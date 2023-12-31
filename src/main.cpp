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

Color get_colour(size_t exp) {
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

class Square {
public:
  size_t exponent;
  bool has_merged;

  Square();
  ~Square();

  bool Occupied() {
    return exponent > 0;
  }

private:
};

Square::Square() {
}

Square::~Square() {
}

class GameGrid {
public:
  GameGrid();
  ~GameGrid();

  void Draw() {
    for (size_t i=0; i<GRIDSIZE; i++) {
      for (size_t j=0; j<GRIDSIZE; j++) {
        int posx = i*width + BORDERWIDTH;
        int posy = j*height + GRIDSTART + BORDERWIDTH;
        DrawRectangle(posx, posy, box_width, box_height, get_colour(squares[i][j].exponent));
        if (squares[i][j].exponent > 0) {
          std::string text = std::format("{}", Value(i, j));
          int text_width = MeasureText(text.c_str(), 64);
          DrawText(text.c_str(), posx + box_width/2 - text_width/2, posy + box_height/2 - 32, 64, BLACK);
        }
      }
    }
  }

  bool MoveLeft() {
    bool squares_were_moved = false;
    for (size_t j=0; j<GRIDSIZE; j++) {
      int i = 1;
      while (i<GRIDSIZE) {
        if (squares[i][j].Occupied() && !squares[i-1][j].Occupied()) {
          squares_were_moved = true;
          squares[i-1][j].exponent = squares[i][j].exponent;
          squares[i][j].exponent = 0;
          if (i>1) i -= 1;
        } else {
          i++;
        }
      }
    }
    return squares_were_moved;
  }

  void MoveRight() {
    for (size_t j=0; j<GRIDSIZE; j++) {
      int i = GRIDSIZE - 2;
      while (i >= 0) {
        if (squares[i][j].Occupied() && !squares[i+1][j].Occupied()) {
          squares[i+1][j].exponent = squares[i][j].exponent;
          squares[i][j].exponent = 0;
          if (i < GRIDSIZE-2) i += 1;
        } else {
          i--;
        }
      }
    }
  }

  void MoveUp() {
    for (size_t i=0; i<GRIDSIZE; i++) {
      int j = 1;
      while (j < GRIDSIZE) {
        if (squares[i][j].Occupied() && !squares[i][j-1].Occupied()) {
          squares[i][j-1].exponent = squares[i][j].exponent;
          squares[i][j].exponent = 0;
          if (j>1) j -= 1;
        } else {
          j++;
        }
      }
    }
  }

  void MoveDown() {
    for (size_t i=0; i<GRIDSIZE; i++) {
      int j = GRIDSIZE - 2;
      while (j >= 0) {
        if (squares[i][j].Occupied() && !squares[i][j+1].Occupied()) {
          squares[i][j+1].exponent = squares[i][j].exponent;
          squares[i][j].exponent = 0;
          if (j < GRIDSIZE-2) j += 1;
        } else {
          j--;
        }
      }
    }
  }

  int getARandomSquare(int *i1, int *j1) {
    int empty_squares = CountEmptySquares();
    if (empty_squares < 1) return -1;
    int square1 = rand() % empty_squares;
    int counter = 0;
    for (size_t i=0; i<GRIDSIZE; i++) {
      for (size_t j=0; j<GRIDSIZE; j++) {
        if (squares[i][j].exponent != 0) continue;
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
  Square squares[GRIDSIZE][GRIDSIZE];

  void Init() {
    squares[2][2].exponent = 1;
    squares[2][1].exponent = 1;
  }

  void StepLeft() {
    for (int i=1; i<GRIDSIZE; i++) {
      for (int j=0; j<GRIDSIZE; j++) {
        if (squares[i][j].exponent == 0) continue;
        if (squares[i-1][j].exponent == 0) {
          squares[i-1][j].exponent = squares[i][j].exponent;
          squares[i][j].exponent = 0;
        } else if (squares[i-1][j].exponent == squares[i][j].exponent) {
          squares[i-1][j].exponent += 1;
          squares[i][j].exponent = 0;
        }
      }
    }
  }

  int Value(int i, int j) {
    return 1 << squares[i][j].exponent;
  }

  int CountEmptySquares() {
    size_t result = 0;
    for (size_t i=0; i<GRIDSIZE; i++) {
      for (size_t j=0; j<GRIDSIZE; j++) {
        if (!squares[i][j].Occupied()) {
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
  for (size_t i=0; i<GRIDSIZE; i++) {
    for (size_t j=0; j<GRIDSIZE; j++) {
      squares[i][j].exponent = 0;
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
    if (IsKeyPressed(KEY_LEFT))  grid.MoveLeft();
    if (IsKeyPressed(KEY_RIGHT)) grid.MoveRight();
    if (IsKeyPressed(KEY_UP))    grid.MoveUp();
    if (IsKeyPressed(KEY_DOWN))  grid.MoveDown();
    BeginDrawing();
    ClearBackground(BACKGROUND_COLOUR);
    grid.Draw();
    EndDrawing();
  }

  std::cout << "Hello world!" << std::endl;

  return 0;
}

