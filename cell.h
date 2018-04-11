

class Cell {
 private:
  int x;
  int y;
  Cell *left;
  Cell *right;
  Cell *top;
  Cell *bottom;

 public:
  Cell(int x, int y) {
    this->x = x;
    this->y = y;
    left = NULL;
    right = NULL;
    top = NULL;
    bottom = NULL;
  }

  void Set(Cell *left, Cell *right, Cell *top, Cell *bottom) {
    if (left) {
      this->left = left;
    }

    if (right) {
      this->right = right;
    }

    if (top) {
      this->top = top;
    }

    if (bottom) {
      this->bottom = bottom;
    }
  }

  void UnSet(Cell *left, Cell *right, Cell *top, Cell *bottom) {
    if (left) {
      this->left = NULL;
    }

    if (right) {
      this->right = NULL;
    }

    if (top) {
      this->top = NULL;
    }

    if (bottom) {
      this->bottom = NULL;
    }
  }
}
