#pragma once

#include <array>
#include <format>

#include "raylib.h"

template <typename T, std::size_t Dim>
using SquareArray = std::array<std::array<T, Dim>, Dim>;

struct coords {
  int row, col;
};

Color get_colour(int number);

class GameGrid {

private:
  static const int grid_start = 100;
  static const int grid_size = 4;
  static const int border_width = 3;

  static const int window_width = 600;
  static const int window_height = window_width + grid_start;
  static constexpr Color background_colour = DARKGRAY;

  int width, height, box_width, box_height;
  SquareArray<int, grid_size> squares;

  int Value(coords);

  int CountEmptySquares();

  void AddNewSquare(coords);
  coords getARandomSquare();

  bool StepLeft();
  bool CompressLeft();
  bool StepRight();
  bool CompressRight();
  bool StepUp();
  bool CompressUp();
  bool StepDown();
  bool CompressDown();

public:
  GameGrid();
  ~GameGrid();

  void RaylibInit();
  void Draw();

  bool MoveLeft();
  bool MoveRight();
  bool MoveUp();
  bool MoveDown();

  void AddRandomSquare();
};


