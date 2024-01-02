#include "gamegrid.h"

Color get_colour(int number) {
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
  return colours[number % 11];
}

void GameGrid::RaylibInit() {
  InitWindow(window_width, window_height, "2048 by Stephen Molloy");
  SetTargetFPS(60);
}

void GameGrid::Draw() {
  ClearBackground(background_colour);
  for (int row=0; row<grid_size; row++) {
    for (int col=0; col<grid_size; col++) {
      const int posx = row*width + border_width;
      const int posy = col*height + grid_start + border_width;
      DrawRectangle(posx, posy, box_width, box_height, get_colour(squares[row][col]));
      if (squares[row][col]> 0) {
        const std::string text = std::format("{}", Value({row, col}));
        const int text_width = MeasureText(text.c_str(), 64);
        DrawText(text.c_str(), posx + box_width/2 - text_width/2, posy + box_height/2 - 32, 64, BLACK);
      }
    }
  }
}

bool GameGrid::MoveLeft() {
  bool result = StepLeft();
  result     |= CompressLeft();
  result     |= StepLeft();
  return result;
}

bool GameGrid::MoveRight() {
  bool result = StepRight();
  result     |= CompressRight();
  result     |= StepRight();
  return result;
}

bool GameGrid::MoveUp() {
  bool result = StepUp();
  result     |= CompressUp();
  result     |= StepUp();
  return result;
}

bool GameGrid::MoveDown() {
  bool result = StepDown();
  result     |= CompressDown();
  result     |= StepDown();
  return result;
}

bool GameGrid::StepLeft() {
  bool squares_were_moved = false;
  for (int col=0; col<grid_size; col++) {
    int row = 1;
    while (row<grid_size) {
      if (squares[row][col] > 0 && squares[row-1][col] == 0) {
        squares_were_moved = true;
        squares[row-1][col] = squares[row][col];
        squares[row][col] = 0;
        if (row>1) row -= 1;
      } else {
        row++;
      }
    }
  }
  return squares_were_moved;
}

bool GameGrid::CompressLeft() {
  bool squares_were_moved = false;
  for (int col=0; col<grid_size; col++) {
    for (int row=1; row<grid_size; row++) {
      if (squares[row][col] > 0 && squares[row][col]==squares[row-1][col]) {
        squares_were_moved = true;
        squares[row-1][col] += 1;
        squares[row][col] = 0;
      }
    }
  }
  return squares_were_moved;
}

bool GameGrid::StepRight() {
  bool squares_were_moved = false;
  for (int col=0; col<grid_size; col++) {
    int row = grid_size - 2;
    while (row >= 0) {
      if (squares[row][col] > 0 && squares[row+1][col] == 0) {
        squares_were_moved = true;
        squares[row+1][col] = squares[row][col];
        squares[row][col] = 0;
        if (row < grid_size-2) row += 1;
      } else {
        row--;
      }
    }
  }
  return squares_were_moved;
}

bool GameGrid::CompressRight() {
  bool squares_were_moved = false;
  for (int col=0; col<grid_size; col++) {
    for (int row=grid_size-2; row>=0; row--) {
      if (squares[row][col] > 0 && squares[row][col]==squares[row+1][col]) {
        squares_were_moved = true;
        squares[row+1][col] += 1;
        squares[row][col] = 0;
      }
    }
  }
  return squares_were_moved;
}

bool GameGrid::StepUp() {
  bool squares_were_moved = false;
  for (int row=0; row<grid_size; row++) {
    int col = 1;
    while (col < grid_size) {
      if (squares[row][col] > 0 && squares[row][col-1] == 0) {
        squares_were_moved = true;
        squares[row][col-1] = squares[row][col];
        squares[row][col] = 0;
        if (col>1) col -= 1;
      } else {
        col++;
      }
    }
  }
  return squares_were_moved;
}

bool GameGrid::CompressUp() {
  bool squares_were_moved = false;
  for (int row=0; row<grid_size; row++) {
    for (int col=1; col<grid_size; col++) {
      if (squares[row][col] > 0 && squares[row][col]==squares[row][col-1]) {
        squares_were_moved = true;
        squares[row][col-1] += 1;
        squares[row][col] = 0;
      }
    }
  }
  return squares_were_moved;
}

bool GameGrid::StepDown() {
  bool squares_were_moved = false;
  for (int row=0; row<grid_size; row++) {
    int col = grid_size - 2;
    while (col >= 0) {
      if (squares[row][col] > 0 && squares[row][col+1] == 0) {
        squares_were_moved = true;
        squares[row][col+1] = squares[row][col];
        squares[row][col] = 0;
        if (col < grid_size-2) col += 1;
      } else {
        col--;
      }
    }
  }
  return squares_were_moved;
}

bool GameGrid::CompressDown() {
  bool squares_were_moved = false;
  for (int row=0; row<grid_size; row++) {
    for (int col=grid_size-2; col>=0; col--) {
      if (squares[row][col] > 0 && squares[row][col]==squares[row][col+1]) {
        squares_were_moved = true;
        squares[row][col+1] += 1;
        squares[row][col] = 0;
      }
    }
  }
  return squares_were_moved;
}

void GameGrid::AddNewSquare(coords pos) {
  squares[pos.row][pos.col]= 1;
}

coords GameGrid::getARandomSquare() {
  int empty_squares = CountEmptySquares();
  if (empty_squares < 1) {
    throw;
  }
  int square1 = rand() % empty_squares;
  int counter = 0;
  for (int row=0; row<grid_size; row++) {
    for (int col=0; col<grid_size; col++) {
      if (squares[row][col] != 0) continue;
      if (square1 == counter) {
        return {row, col};
      }
      counter++;
    }
  }
  throw;
}

void GameGrid::AddRandomSquare() {
  AddNewSquare(getARandomSquare());
}

int GameGrid::Value(coords pos) {
  return 1 << squares[pos.row][pos.col];
}

int GameGrid::CountEmptySquares() {
  int result = 0;
  for (int row=0; row<grid_size; row++) {
    for (int col=0; col<grid_size; col++) {
      if (!(squares[row][col] > 0)) {
        result++;
      }
    }
  }
  return result;
}

GameGrid::GameGrid() {
  width = window_width / grid_size;
  height = width;
  box_width = width - 2*border_width;
  box_height = box_width;
  for (int row=0; row<grid_size; row++) {
    for (int col=0; col<grid_size; col++) {
      squares[row][col] = 0;
    }
  }

  squares[0][0] = 1;
  squares[1][0] = 1;
}

GameGrid::~GameGrid() {
}

