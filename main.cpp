#include <ncurses.h>
#include "maze.h"
#include <string>
#include <unistd.h>
#include <stdio.h>

enum PROG_MODE { DRAW, SERVER } ProgMode;

void DrawMode(WINDOW* mainWindow, Maze* M) {
  bool closeWindow = FALSE;
  while(int ch = getch()) {
    switch(ch) {
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

int main(int argc, char* argv[]) {
  ProgMode = DRAW;
  std::string fname("");
  int ch;
  while ((ch = getopt(argc, argv, "dsf:")) != -1) {
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
  }

  endwin();
}
