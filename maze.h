#include <ncurses.h>
#include <set>
#include "room.h"
#include <cstdlib>
#include <algorithm>

class Maze {
 private:
  int length;
  int height;
  Cell *head;
  Cell ***mazeMap;
  std::set<Room*> bag;

  void drawBorder() {
    for (int i = 0; i <= length; i++) {
      mvaddch(0,i,'#');
      mvaddch(height,i,'#');
    }

    for (int i =0; i <= height;i++) {
      mvaddch(i,0,'#');
      mvaddch(i,length,'#');
    }
  }

  void allocateMazeMap() {
    mazeMap = new Cell**[(length-1)/2];
    for (int i = 0; i <= length; i+=2) {
      mazeMap[i/2] = new Cell*[(height-1)/2];
    }
  }


 public:

  Maze(int length, int height) {
    this->length = length;
    this->height = height;
    allocateMazeMap();
  }

  ~Maze() {
    for (std::set<Room*>::iterator iter = bag.begin();
         iter != bag.end(); iter++) {
      Room* r = *iter;
      delete(r);
    }
  }

  void Draw() {
    drawBorder();
  }
};
