#include "raylib.h"

#include "gamegrid.h"

int main(void) {
  GameGrid grid;
  grid.RaylibInit();

  while (!WindowShouldClose()) {
    if (IsKeyPressed(KEY_LEFT))  {
      if (grid.MoveLeft()) {
        grid.AddRandomSquare();
      }
    }
    if (IsKeyPressed(KEY_RIGHT)) {
      if (grid.MoveRight()){
        grid.AddRandomSquare();
      }
    }
    if (IsKeyPressed(KEY_UP)) {
      if (grid.MoveUp()) {
        grid.AddRandomSquare();
      }
    }
    if (IsKeyPressed(KEY_DOWN)) {
      if (grid.MoveDown()) {
        grid.AddRandomSquare();
      }
    }

    BeginDrawing();
      grid.Draw();
    EndDrawing();
  }

  return 0;
}

