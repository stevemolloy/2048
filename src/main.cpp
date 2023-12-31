#include <cassert>
#include <cmath>
#include <cstdlib>
#include <format>
#include <iostream>
#include <random>
#include <string>

#include "raylib.h"

#define GRIDSTART 100
#define GRIDSIZE 4
#define BORDERWIDTH 3

#define WIDTH 600
#define HEIGHT (WIDTH + GRIDSTART)

#define BACKGROUND_COLOUR DARKGRAY

Color get_colour(int exp) {
  Color colours[11] = {
    BLACK,
    YELLOW,
    GOLD,  
    ORANGE,   
    PINK,  
    RED,    
    MAROON,   
    GREEN,  
    LIME,   
    DARKGREEN,
    SKYBLUE,
  };
  return colours[exp % 11];
}

class GameGrid {
public:
  GameGrid();
  ~GameGrid();

  void Draw() {
    for (int i=0; i<GRIDSIZE; i++) {
      for (int j=0; j<GRIDSIZE; j++) {
        int posx = i*width + BORDERWIDTH;
        int posy = j*height + GRIDSTART + BORDERWIDTH;
        DrawRectangle(posx, posy, box_width, box_height, get_colour(squares[i][j]));
        if (squares[i][j]> 0) {
          std::string text = std::format("{}", Value(i, j));
          int text_width = MeasureText(text.c_str(), 64);
          DrawText(text.c_str(), posx + box_width/2 - text_width/2, posy + box_height/2 - 32, 64, BLACK);
        }
      }
    }
  }

  void AddNewSquare(int i, int j) {
    squares[i][j]= 1;
  }

  bool MoveLeft() {
    bool squares_were_moved = false;
    for (int j=0; j<GRIDSIZE; j++) {
      int i = 1;
      while (i<GRIDSIZE) {
        if (squares[i][j] > 0 && squares[i-1][j] == 0) {
          squares_were_moved = true;
          squares[i-1][j] = squares[i][j];
          squares[i][j] = 0;
          if (i>1) i -= 1;
        } else {
          i++;
        }
      }
    }
    return squares_were_moved;
  }

  bool CompressLeft() {
    bool squares_were_moved = false;
    for (int j=0; j<GRIDSIZE; j++) {
      for (int i=1; i<GRIDSIZE; i++) {
        if (squares[i][j] > 0 && squares[i][j]==squares[i-1][j]) {
          squares_were_moved = true;
          squares[i-i][j] += 1;
          squares[i][j] = 0;
        }
      }
    }
    return squares_were_moved;
  }

  bool MoveRight() {
    bool squares_were_moved = false;
    for (int j=0; j<GRIDSIZE; j++) {
      int i = GRIDSIZE - 2;
      while (i >= 0) {
        if (squares[i][j] > 0 && squares[i+1][j] == 0) {
          squares_were_moved = true;
          squares[i+1][j] = squares[i][j];
          squares[i][j] = 0;
          if (i < GRIDSIZE-2) i += 1;
        } else {
          i--;
        }
      }
    }
    return squares_were_moved;
  }

  bool CompressRight() {
    bool squares_were_moved = false;
    for (int j=0; j<GRIDSIZE; j++) {
      for (int i=GRIDSIZE-2; i>=0; i--) {
        if (squares[i][j] > 0 && squares[i][j]==squares[i+1][j]) {
          squares_were_moved = true;
          assert((i+1) < GRIDSIZE);
          squares[i+i][j] += 1;
          squares[i][j] = 0;
        }
      }
    }
    return squares_were_moved;
  }

  bool MoveUp() {
    bool squares_were_moved = false;
    for (int i=0; i<GRIDSIZE; i++) {
      int j = 1;
      while (j < GRIDSIZE) {
        if (squares[i][j] > 0 && squares[i][j-1] == 0) {
          squares_were_moved = true;
          squares[i][j-1] = squares[i][j];
          squares[i][j] = 0;
          if (j>1) j -= 1;
        } else {
          j++;
        }
      }
    }
    return squares_were_moved;
  }

  bool CompressUp() {
    bool squares_were_moved = false;
    for (int i=0; i<GRIDSIZE; i++) {
      for (int j=1; j<GRIDSIZE; j++) {
        if (squares[i][j] > 0 && squares[i][j]==squares[i][j-1]) {
          squares_were_moved = true;
          squares[i][j-1] += 1;
          squares[i][j] = 0;
        }
      }
    }
    return squares_were_moved;
  }

  bool MoveDown() {
    bool squares_were_moved = false;
    for (int i=0; i<GRIDSIZE; i++) {
      int j = GRIDSIZE - 2;
      while (j >= 0) {
        if (squares[i][j] > 0 && squares[i][j+1] == 0) {
          squares_were_moved = true;
          squares[i][j+1] = squares[i][j];
          squares[i][j] = 0;
          if (j < GRIDSIZE-2) j += 1;
        } else {
          j--;
        }
      }
    }
    return squares_were_moved;
  }

  bool CompressDown() {
    bool squares_were_moved = false;
    for (int i=0; i<GRIDSIZE; i++) {
      for (int j=GRIDSIZE-2; j>=0; j--) {
        if (squares[i][j] > 0 && squares[i][j]==squares[i][j+1]) {
          squares_were_moved = true;
          squares[i][j+1] += 1;
          squares[i][j] = 0;
        }
      }
    }
    return squares_were_moved;
  }

  int getARandomSquare(int *i1, int *j1) {
    int empty_squares = CountEmptySquares();
    if (empty_squares < 1) return -1;
    int square1 = rand() % empty_squares;
    int counter = 0;
    for (int i=0; i<GRIDSIZE; i++) {
      for (int j=0; j<GRIDSIZE; j++) {
        if (squares[i][j] != 0) continue;
        if (square1 == counter) {
          *i1 = i;
          *j1 = j;
        }
        counter++;
      }
    }
    return 1;
  }

private:
  int width, height, box_width, box_height;
  int squares[GRIDSIZE][GRIDSIZE];

  void Init() {
    squares[0][0] = 1;
    squares[1][0] = 1;
  }

  void StepLeft() {
    for (int i=1; i<GRIDSIZE; i++) {
      for (int j=0; j<GRIDSIZE; j++) {
        if (squares[i][j] == 0) continue;
        if (squares[i-1][j] == 0) {
          squares[i-1][j] = squares[i][j];
          squares[i][j] = 0;
        } else if (squares[i-1][j] == squares[i][j]) {
          squares[i-1][j] += 1;
          squares[i][j] = 0;
        }
      }
    }
  }

  int Value(int i, int j) {
    return 1 << squares[i][j];
  }

  int CountEmptySquares() {
    int result = 0;
    for (int i=0; i<GRIDSIZE; i++) {
      for (int j=0; j<GRIDSIZE; j++) {
        if (!(squares[i][j] > 0)) {
          result++;
        }
      }
    }
    return result;
  }
};

GameGrid::GameGrid() {
  width = WIDTH / GRIDSIZE;
  height = width;
  box_width = width - 2*BORDERWIDTH;
  box_height = box_width;
  for (int i=0; i<GRIDSIZE; i++) {
    for (int j=0; j<GRIDSIZE; j++) {
      squares[i][j] = 0;
    }
  }

  Init();
}

GameGrid::~GameGrid() {
}

int main(void) {
  GameGrid grid = GameGrid();

  InitWindow(WIDTH, HEIGHT, "2048 by Stephen Molloy");
  SetTargetFPS(60);

  while (!WindowShouldClose()) {
    if (IsKeyPressed(KEY_LEFT))  {
      bool squares_were_moved = grid.MoveLeft();
      squares_were_moved     |= grid.CompressLeft();
      squares_were_moved     |= grid.MoveLeft();
      if (squares_were_moved) {
        int i, j;
        grid.getARandomSquare(&i, &j);
        grid.AddNewSquare(i, j);
      }
    }
    if (IsKeyPressed(KEY_RIGHT)) {
      bool squares_were_moved = grid.MoveRight();
      squares_were_moved     |= grid.CompressRight();
      squares_were_moved     |= grid.MoveRight();
      if (squares_were_moved) {
        int i, j;
        grid.getARandomSquare(&i, &j);
        grid.AddNewSquare(i, j);
      }
    }
    if (IsKeyPressed(KEY_UP)) {
      bool squares_were_moved = grid.MoveUp();
      squares_were_moved     |= grid.CompressUp();
      squares_were_moved     |= grid.MoveUp();
      if (squares_were_moved) {
        int i, j;
        grid.getARandomSquare(&i, &j);
        grid.AddNewSquare(i, j);
      }
    }
    if (IsKeyPressed(KEY_DOWN)) {
      bool squares_were_moved = grid.MoveDown();
      squares_were_moved     |= grid.CompressDown();
      squares_were_moved     |= grid.MoveDown();
      if (squares_were_moved) {
        int i, j;
        grid.getARandomSquare(&i, &j);
        grid.AddNewSquare(i, j);
      }
    }
    BeginDrawing();
    ClearBackground(BACKGROUND_COLOUR);
    grid.Draw();
    EndDrawing();
  }

  return 0;
}

