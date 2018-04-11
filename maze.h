#include <ncurses.h>
#include <set>
#include "room.h"
#include "cell.h"
#include <fstream>
#include <string>

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
    mazeMap = new Cell**[length-1];
    for (int i = 0; i < length-1; i++) {
      mazeMap[i] = new Cell*[height-1];
      for (int j = 0; j < (height - 1); j++) {
        mazeMap[i][j]=new Cell(i,j,BLANK);
      }
    }
  }


  void LoadMazeMap(std::string fname) {
    std::fstream fs(fname,std::fstream::in);
    fs>>this->length>>this->height;

    allocateMazeMap();

    while (!fs.eof()) {
      int x, y;
      char piece;
      char dir;
      fs >> x >> y >> piece;
      switch(piece) {
      case '#':
        mazeMap[x][y]->type = WALL;
        break;
      case 'X':
        mazeMap[x][y]->type = X;
        break;
      case '>':
        mazeMap[x][y]->type = HERO;
        fs >> dir;
        switch(dir) {
        case 'u':
          mazeMap[x][y]->dir = SCREEN_UP;
          break;
        case 'd':
          mazeMap[x][y]->dir = SCREEN_DOWN;
          break;
        case 'l':
          mazeMap[x][y]->dir = SCREEN_LEFT;
          break;
        case 'r':
          mazeMap[x][y]->dir = SCREEN_RIGHT;
          break;
        }
        break;
      }
    }
    fs.close();
  }

 public:

  Maze(std::string fname) {
    LoadMazeMap(fname);
  }

  Maze(int length, int height) {
    this->length = length;
    this->height = height;
    allocateMazeMap();
  }

  void SaveMazeMap(std::string fname) {
    std::fstream fs(fname,std::fstream::out|std::fstream::trunc);
    fs<<this->length<<" "<<this->height<<std::endl;
    for (int i = 0; i < length-1; i++) {
      for (int j = 0; j < (height - 1); j++) {
        Cell *cell = mazeMap[i][j];
        switch(cell->type) {
        case WALL:
          fs<<i<<" "<<j<<" #"<<std::endl;
          break;
        case HERO:
          fs<<i<<" "<<j<<" >";
          switch(cell->dir) {
          case SCREEN_UP:
            fs<<" u";
            break;
          case SCREEN_DOWN:
            fs<<" d";
            break;
          case SCREEN_LEFT:
            fs<<" l";
            break;
          case SCREEN_RIGHT:
            fs<<" r";
            break;
          }
          fs<<std::endl;
          break;
        case X:
          fs<<i<<" "<<j<<" X"<<std::endl;
          break;
        }
      }
    }
    fs.close();
  }

  void PlaceWall(int x, int y) {
    mazeMap[x - 1][y - 1]->type = WALL;
    drawWall(x,y);
  }

  void PlaceBlank(int x, int y) {
    mazeMap[x - 1][y - 1]->type = BLANK;
    drawBlank(x,y);
  }

  void PlaceX(int x, int y) {
    mazeMap[x - 1][y - 1]->type = X;
    drawX(x,y);
  }

  void PlaceHero(int x, int y, enum DIRECTION d) {
    Cell* c = mazeMap[x-1][y-1];
    c->type = HERO;
    c->dir = d;
    drawHero(x,y,d);
  }

  void MoveCursor(int x, int y, enum DIRECTION d) {
    switch(d) {
    case SCREEN_UP:
      y = y - 1;
      break;
    case SCREEN_DOWN:
      y = y + 1;
      break;
    case SCREEN_RIGHT:
      x = x + 1;
      break;
    case SCREEN_LEFT:
      x = x - 1;
      break;
    }

    if (x > 0 && x < length && y > 0 && y < height) {
      move(y,x);
    }
  }

  ~Maze() {
    for (std::set<Room*>::iterator iter = bag.begin();
         iter != bag.end(); iter++) {
      Room* r = *iter;
      delete(r);
    }
  }

  void drawWall(int x, int y) {
    mvaddch(y,x,'#');
    move(y,x);
  }

  void drawBlank(int x, int y) {
    mvaddch(y,x,' ');
    move(y,x);
  }

  void drawX(int x, int y) {
    mvaddch(y,x,'X');
    move(y,x);
  }

  void drawHero(int x, int y, enum DIRECTION d) {
    mvaddch(y,x,getHeroIcon(d));
    move(y,x);
  }

  char getHeroIcon(enum DIRECTION d) {
    char ch = '>';
    switch(d) {
    case SCREEN_UP:
      ch = '^';
      break;
    case SCREEN_DOWN:
      ch = 'v';
      break;
    case SCREEN_LEFT:
      ch = '<';
      break;
    case SCREEN_RIGHT:
      ch = '>';
      break;
    }
    return ch;
  }

  void drawMap() {
    for (int j = 0; j < (height-1); j++) {
      for (int i = 0; i <(length-1); i++) {
        char ch = ' ';
        switch(mazeMap[i][j]->getType()) {
        case BLANK:
          ch = ' ';
          break;
        case WALL:
          ch = '#';
          break;
        case HERO:
          ch = getHeroIcon(mazeMap[i][j]->getDir());
          break;
        case X:
          ch = 'X';
          break;
        }
        mvaddch(j+1,i+1,ch);
      }
    }
  }

  void Draw() {
    drawBorder();
    drawMap();
    move(1,1);
  }
};
