#include <ncurses.h>
#include "maze.h"


int main() {
  initscr();
  cbreak();
  noecho();

  Maze *M = new Maze(75,30);
  M->Draw();
  getch();
  endwin();
}
