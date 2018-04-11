#include <ncurses.h>
#include "maze.h"
#include <string>


int main() {
  WINDOW* mainWindow = initscr();
  cbreak();
  noecho();
  keypad(mainWindow, TRUE);

  Maze *M = new Maze(75,30);
  M->Draw();
  bool closeWindow = false;
 
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
  endwin();
}
