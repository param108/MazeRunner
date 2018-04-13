#include <ncurses.h>
#include "maze.h"
#include <string>
#include <unistd.h>
#include <stdio.h>
#include <microhttpd.h>
#include <iostream>
#include <fstream>
#include <string.h>
#include "nlohmann/json.hpp"

// for convenience
using json = nlohmann::json;

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
Maze* TheMaze;


static const char* handle_request(const char * requestJson) {
  json req = json::parse(requestJson);
  std::string action = req["action"];
  if (action == "FORWARD") {
    if (TheMaze->MoveHero(FORWARD)<0) {
      return "{\"status\": -1}";
    }
  }
  if (action == "TURN_RIGHT") {
    if (TheMaze->MoveHero(TURN_RIGHT)<0) {
      return "{\"status\": -1}";
    }
  }
  if (action == "TURN_LEFT") {
    if (TheMaze->MoveHero(TURN_LEFT)<0) {
      return "{\"status\": -1}";
    }
  }
  refresh();
  return ("{\"status\": 0}");
}

static int move_handler(void * cls,
                        struct MHD_Connection * connection,
                        const char * url,
                        const char * method,
                        const char * version,
                        const char * upload_data,
                        size_t * upload_data_size,
                        void ** ptr) {
  static int dummy;
  struct MHD_Response * response;
  int ret;

  if (std::string(method) != "POST") {
    (*logfs)<<"Not POST"<<std::endl;
    return MHD_NO; /* unexpected method */
  }

  if (*ptr == NULL) {
    // The first time only the headers are valid,
    //   do not respond in the first round...
    *ptr = new char[100];
    return MHD_YES;
  }

  if (*upload_data_size > 0) {
    strcpy((char*)*ptr, handle_request(upload_data));
    *upload_data_size = 0;
    return MHD_YES;
  }

  response = MHD_create_response_from_buffer (strlen((char*)*ptr),
                                              *ptr,
                                              MHD_RESPMEM_MUST_COPY);
  if (response == NULL) {
    (*logfs)<<"response is NULL"<<std::endl;
    return MHD_NO;
  }
  ret = MHD_add_response_header (response,
                                 MHD_HTTP_HEADER_CONTENT_TYPE,
                                 "application/json");
  ret = MHD_queue_response(connection,
                           MHD_HTTP_OK,
                           response); 
  MHD_destroy_response(response);
  delete((char*)*ptr);

  return MHD_YES;
}

int createServerThreads(std::string port, char *page) {
  logfs= new std::fstream("logstash.txt",std::fstream::out|std::fstream::app);
  httpd = MHD_start_daemon(MHD_USE_SELECT_INTERNALLY|MHD_USE_DEBUG,
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

  MHD_run(httpd);
}

char defaultPage[] = "<http>OK</http>";

void ServerMode(WINDOW* mainWindow, Maze* M, std::string port) {
  bool closeWindow = FALSE;
  if (createServerThreads(port,defaultPage) < 0) {
    std::cout<<"Failed to start Server Thread"<<std::endl;
    logfs->close();
    return;
  }

  TheMaze = M;

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
