enum CELL_TYPE { WALL, BLANK, HERO, X };
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
