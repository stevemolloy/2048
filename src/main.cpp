#include <iostream>

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
      }
    }
  }

private:
  int width, height, box_width, box_height;
  size_t exponents[GRIDSIZE][GRIDSIZE];
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
}

GameGrid::~GameGrid() {
}

int main(void) {
  GameGrid grid = GameGrid();

  InitWindow(WIDTH, HEIGHT, "2048 by Stephen Molloy");
  SetTargetFPS(60);

  while (!WindowShouldClose()) {
    BeginDrawing();
    ClearBackground(BACKGROUND_COLOUR);
    grid.Draw();
    EndDrawing();
  }

  std::cout << "Hello world!" << std::endl;

  return 0;
}

