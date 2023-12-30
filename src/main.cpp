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

class GameGrid {
public:
  GameGrid();
  ~GameGrid();

  void Draw() {
    for (size_t i=0; i<GRIDSIZE; i++) {
      for (size_t j=0; j<GRIDSIZE; j++) {
        int posx = i*width + BORDERWIDTH;
        int posy = j*height + GRIDSTART + BORDERWIDTH;
        DrawRectangle(posx, posy, box_width, box_height, get_colour(exponents[i][j]));
        if (exponents[i][j] > 0) {
          std::string text = std::format("{}", Value(i, j));
          int text_width = MeasureText(text.c_str(), 64);
          DrawText(text.c_str(), posx + box_width/2 - text_width/2, posy + box_height/2 - 32, 64, BLACK);
        }
      }
    }
  }

  void MoveLeft() {
    for (int i=GRIDSIZE-1; i>0; i--) {
      for (int j=0; j<GRIDSIZE; j++) {
        if (exponents[i][j] == 0) continue;
        if (exponents[i-1][j] == 0) {
          exponents[i-1][j] = exponents[i][j];
          exponents[i][j] = 0;
        } else if (exponents[i-1][j] == exponents[i][j]) {
          exponents[i-1][j] += 1;
          exponents[i][j] = 0;
        }
      }
    }
    int i1, j1;
    getARandomSquare(&i1, &j1);
    exponents[i1][j1] = 4;
  }

  void MoveRight() {
    for (int i=0; i<GRIDSIZE-1; i++) {
      for (int j=0; j<GRIDSIZE; j++) {
        if (exponents[i][j] == 0) continue;
        if (exponents[i+1][j] == 0) {
          exponents[i+1][j] = exponents[i][j];
          exponents[i][j] = 0;
        } else if (exponents[i+1][j] == exponents[i][j]) {
          exponents[i+1][j] += 1;
          exponents[i][j] = 0;
        }
      }
    }
    int i1, j1;
    getARandomSquare(&i1, &j1);
    exponents[i1][j1] = 4;
  }

  void MoveUp() {
    for (int i=0; i<GRIDSIZE; i++) {
      for (int j=GRIDSIZE-1; j>0; j--) {
        if (exponents[i][j] == 0) continue;
        if (exponents[i][j-1] == 0) {
          exponents[i][j-1] = exponents[i][j];
          exponents[i][j] = 0;
        } else if (exponents[i][j-1] == exponents[i][j]) {
          exponents[i][j-1] += 1;
          exponents[i][j] = 0;
        }
      }
    }
    int i1, j1;
    getARandomSquare(&i1, &j1);
    exponents[i1][j1] = 4;
  }

  void MoveDown() {
    for (int i=0; i<GRIDSIZE; i++) {
      for (int j=0; j<GRIDSIZE-1; j++) {
        if (exponents[i][j] == 0) continue;
        if (exponents[i][j+1] == 0) {
          exponents[i][j+1] = exponents[i][j];
          exponents[i][j] = 0;
        } else if (exponents[i][j+1] == exponents[i][j]) {
          exponents[i][j+1] += 1;
          exponents[i][j] = 0;
        }
      }
    }
    int i1, j1;
    getARandomSquare(&i1, &j1);
    exponents[i1][j1] = 4;
  }

  int getARandomSquare(int *i1, int *j1) {
    int empty_squares = CountEmptySquare();
    if (empty_squares < 1) return -1;
    int square1 = rand() % empty_squares;
    int counter = 0;
    for (size_t i=0; i<GRIDSIZE; i++) {
      for (size_t j=0; j<GRIDSIZE; j++) {
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
  size_t exponents[GRIDSIZE][GRIDSIZE];

  void Init() {
    exponents[1][2] = 1;
    exponents[0][1] = 1;
  }

  int Value(int i, int j) {
    return 1 << exponents[i][j];
  }

  int CountEmptySquare() {
    size_t result = 0;
    for (size_t i=0; i<GRIDSIZE; i++) {
      for (size_t j=0; j<GRIDSIZE; j++) {
        if (exponents[i][j] == 0) result++;
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
      exponents[i][j] = 0;
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

