#include <string>

enum CELL_TYPE { WALL, BLANK, HERO, X };

std::string cellTypeToString(enum CELL_TYPE c) {
  switch(c) {
  case WALL:
    return std::string("WALL");
  case BLANK:
    return std::string("BLANK");
  case HERO:
    return std::string("HERO");
  case X:
    return std::string("X");
  }
}

enum DIRECTION {SCREEN_UP, SCREEN_DOWN, SCREEN_LEFT, SCREEN_RIGHT};
class Cell {
 public:
  enum CELL_TYPE type;
  enum DIRECTION dir;
  int x;
  int y;

  Cell(int x, int y, enum CELL_TYPE type) {
    this->type = type;
    this->x = x;
    this->y = y;
    this->dir = SCREEN_UP;
  }

  Cell(int x, int y, enum CELL_TYPE type, enum DIRECTION dir) {
    this->type = type;
    this->x = x;
    this->y = y;
    this->dir = dir;
  }

  enum CELL_TYPE getType() {
    return type;
  }

  enum DIRECTION getDir() {
    return dir;
  }
};
