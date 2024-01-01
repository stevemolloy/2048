#pragma once

#include <array>
#include <format>

#include "raylib.h"

constexpr int grid_start = 100;
constexpr int grid_size = 4;
constexpr int border_width = 3;

constexpr int window_width = 600;
constexpr int window_height = window_width + grid_start;

constexpr Color background_colour = DARKGRAY;

template <typename T, std::size_t Dim>
using SquareArray = std::array<std::array<T, Dim>, Dim>;

Color get_colour(int number);

class GameGrid {
public:
  GameGrid();
  ~GameGrid();

  void Draw();

  void AddNewSquare(int i, int j);

  bool MoveLeft();
  bool CompressLeft();
  bool MoveRight();
  bool CompressRight();
  bool MoveUp();
  bool CompressUp();
  bool MoveDown();
  bool CompressDown();

  int getARandomSquare(int *i1, int *j1);

private:
  int width, height, box_width, box_height;
  SquareArray<int, grid_size> squares;

  void StepLeft();

  int Value(int i, int j);

  int CountEmptySquares();
};


