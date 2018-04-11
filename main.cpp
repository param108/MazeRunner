#include <ncurses.h>
#include "maze.h"
#include <string>
#include <unistd.h>
#include <stdio.h>
#include <microhttpd.h>
#include <iostream>
#include <fstream>

#define PAGE "<html>OK</html>"

enum PROG_MODE { DRAW, SERVER } ProgMode;

void DrawMode(WINDOW* mainWindow, Maze* M) {
  bool closeWindow = FALSE;
  while(int ch = getch()) {
    switch(ch) {
    case 'x':
      M->PlaceX(getcurx(mainWindow),getcury(mainWindow));
      break;
    case 'w':
      M->PlaceWall(getcurx(mainWindow),getcury(mainWindow));
      break;
    case 'u':
      M->PlaceHero(getcurx(mainWindow),getcury(mainWindow),SCREEN_UP);
      break;
    case 'd':
      M->PlaceHero(getcurx(mainWindow),getcury(mainWindow),SCREEN_DOWN);
      break;
    case 'l':
      M->PlaceHero(getcurx(mainWindow),getcury(mainWindow),SCREEN_LEFT);
      break;
    case 'r':
      M->PlaceHero(getcurx(mainWindow),getcury(mainWindow),SCREEN_RIGHT);
      break;
    case KEY_UP:
      M->MoveCursor(getcurx(mainWindow),getcury(mainWindow),SCREEN_UP);
      break;
    case KEY_DOWN:
      M->MoveCursor(getcurx(mainWindow),getcury(mainWindow),SCREEN_DOWN);
      break;
    case KEY_LEFT:
      M->MoveCursor(getcurx(mainWindow),getcury(mainWindow),SCREEN_LEFT);
      break;
    case KEY_RIGHT:
      M->MoveCursor(getcurx(mainWindow),getcury(mainWindow),SCREEN_RIGHT);
      break;
    case 's':
      M->SaveMazeMap(std::string("mazemap.txt"));
      break;
    case 'q':
      closeWindow = TRUE;
      break;
    case ' ':
      M->PlaceBlank(getcurx(mainWindow), getcury(mainWindow));
      break;
    case 'z':
      M->Draw();
      break;
    }

    if (closeWindow) {
      break;
    } else {
      refresh();
    }
  }
}

struct MHD_Daemon* httpd;
std::fstream *logfs;

static int move_handler(void * cls,
                        struct MHD_Connection * connection,
                        const char * url,
                        const char * method,
                        const char * version,
                        const char * upload_data,
                        size_t * upload_data_size,
                        void ** ptr) {
  static int dummy;
  std::string page((const char*)cls);
  struct MHD_Response * response;
  int ret;

  if (std::string(method) != "POST") {
    (*logfs)<<"Not POST"<<std::endl;
    return MHD_NO; /* unexpected method */
  }

  if (&dummy != *ptr)
    {
      // The first time only the headers are valid,
      //   do not respond in the first round...
      (*logfs) << "Empty Response"<<std::endl;
      *ptr = &dummy;
      return MHD_YES;
    }
  if (0 == *upload_data_size) {
    (*logfs)<<"invalid upload_data"<<std::endl;
    return MHD_NO; /* no upload data in a POST? */
  } else {
    (*logfs)<<"Recieved:"<<upload_data<<" "<<page.length()<<std::endl;
  }
  *ptr = NULL; /* clear context pointer */
  response = MHD_create_response_from_buffer (page.length(),
                                              (void*) page.c_str(),
                                              MHD_RESPMEM_MUST_COPY);
  MHD_add_response_header (response,
                                  MHD_HTTP_HEADER_CONTENT_TYPE,
                                  "application/json");

  (*logfs)<<page<<std::endl;
  if (response == NULL) {
    (*logfs)<<"response is NULL"<<std::endl;
  }
  ret = MHD_queue_response(connection,
                           MHD_HTTP_OK,
                           response);
  MHD_destroy_response(response);
  (*logfs)<<"Sent response"<<ret<<std::endl;
  return ret;
}

int createServerThreads(std::string port, char *page) {
  logfs= new std::fstream("logstash.txt",std::fstream::out|std::fstream::app);
  httpd = MHD_start_daemon(MHD_USE_THREAD_PER_CONNECTION,
                           atoi(port.c_str()),
                           NULL,
                           NULL,
                           &move_handler,
                           page,
                           MHD_OPTION_END);
  if (httpd == NULL) {
    (*logfs)<<"Failed to create server"<<std::endl;
    return -1;
  }
}

char defaultPage[] = "<http>OK</http>";

void ServerMode(WINDOW* mainWindow, Maze* M, std::string port) {
  bool closeWindow = FALSE;
  if (createServerThreads(port,defaultPage) < 0) {
    std::cout<<"Failed to start Server Thread"<<std::endl;
    logfs->close();
    return;
  }

  while(int ch = getch()) {
    switch(ch) {
    case KEY_UP:
      M->MoveHero(FORWARD);
      break;
    case KEY_LEFT:
      M->MoveHero(TURN_LEFT);
      break;
    case KEY_RIGHT:
      M->MoveHero(TURN_RIGHT);
      break;
    case 'q':
      closeWindow = TRUE;
      break;
    case 'z':
      M->ReloadMazeMap();
      M->Draw();
      break;
    }

    if (closeWindow) {
      break;
    } else {
      refresh();
    }
  }
  MHD_stop_daemon(httpd);
  logfs->close();
}

int main(int argc, char* argv[]) {
  ProgMode = DRAW;
  std::string fname("");
  std::string port("8080");
  int ch;
  while ((ch = getopt(argc, argv, "dsf:p:")) != -1) {
    switch(ch) {
    case 's':
      ProgMode = SERVER;
      break;
    case 'd':
      ProgMode = DRAW;
      break;
    case 'f':
      fname = optarg;
      break;
    case 'p':
      port = optarg;
    }
  }


  Maze *M;
  if (fname.length() == 0) {
    M = new Maze(75,30);
  } else {
    M = new Maze(fname);
  }

  WINDOW* mainWindow = initscr();
  cbreak();
  noecho();
  keypad(mainWindow, TRUE);

  M->Draw();
  bool closeWindow = false;

  if (ProgMode == DRAW) {
    DrawMode(mainWindow, M);
  } else {
    /* FIXME */
    ServerMode(mainWindow, M, port);
  }

  endwin();
}
