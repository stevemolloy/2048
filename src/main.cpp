#include <array>
#include <cassert>
#include <cmath>
#include <cstdlib>
#include <format>
#include <iostream>
#include <random>
#include <string>

#include "raylib.h"

#include "gamegrid.h"

int main(void) {
  GameGrid grid = GameGrid();

  InitWindow(window_width, window_height, "2048 by Stephen Molloy");
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
    ClearBackground(background_colour);
    grid.Draw();
    EndDrawing();
  }

  return 0;
}

