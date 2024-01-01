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

void GameGrid::Draw() {
  for (int i=0; i<grid_size; i++) {
    for (int j=0; j<grid_size; j++) {
      const int posx = i*width + border_width;
      const int posy = j*height + grid_start + border_width;
      DrawRectangle(posx, posy, box_width, box_height, get_colour(squares[i][j]));
      if (squares[i][j]> 0) {
        const std::string text = std::format("{}", Value(i, j));
        const int text_width = MeasureText(text.c_str(), 64);
        DrawText(text.c_str(), posx + box_width/2 - text_width/2, posy + box_height/2 - 32, 64, BLACK);
      }
    }
  }
}

void GameGrid::AddNewSquare(int i, int j) {
  squares[i][j]= 1;
}

bool GameGrid::MoveLeft() {
  bool squares_were_moved = false;
  for (int j=0; j<grid_size; j++) {
    int i = 1;
    while (i<grid_size) {
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

bool GameGrid::CompressLeft() {
  bool squares_were_moved = false;
  for (int j=0; j<grid_size; j++) {
    for (int i=1; i<grid_size; i++) {
      if (squares[i][j] > 0 && squares[i][j]==squares[i-1][j]) {
        squares_were_moved = true;
        squares[i-1][j] += 1;
        squares[i][j] = 0;
      }
    }
  }
  return squares_were_moved;
}

bool GameGrid::MoveRight() {
  bool squares_were_moved = false;
  for (int j=0; j<grid_size; j++) {
    int i = grid_size - 2;
    while (i >= 0) {
      if (squares[i][j] > 0 && squares[i+1][j] == 0) {
        squares_were_moved = true;
        squares[i+1][j] = squares[i][j];
        squares[i][j] = 0;
        if (i < grid_size-2) i += 1;
      } else {
        i--;
      }
    }
  }
  return squares_were_moved;
}

bool GameGrid::CompressRight() {
  bool squares_were_moved = false;
  for (int j=0; j<grid_size; j++) {
    for (int i=grid_size-2; i>=0; i--) {
      if (squares[i][j] > 0 && squares[i][j]==squares[i+1][j]) {
        squares_were_moved = true;
        squares[i+1][j] += 1;
        squares[i][j] = 0;
      }
    }
  }
  return squares_were_moved;
}

bool GameGrid::MoveUp() {
  bool squares_were_moved = false;
  for (int i=0; i<grid_size; i++) {
    int j = 1;
    while (j < grid_size) {
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

bool GameGrid::CompressUp() {
  bool squares_were_moved = false;
  for (int i=0; i<grid_size; i++) {
    for (int j=1; j<grid_size; j++) {
      if (squares[i][j] > 0 && squares[i][j]==squares[i][j-1]) {
        squares_were_moved = true;
        squares[i][j-1] += 1;
        squares[i][j] = 0;
      }
    }
  }
  return squares_were_moved;
}

bool GameGrid::MoveDown() {
  bool squares_were_moved = false;
  for (int i=0; i<grid_size; i++) {
    int j = grid_size - 2;
    while (j >= 0) {
      if (squares[i][j] > 0 && squares[i][j+1] == 0) {
        squares_were_moved = true;
        squares[i][j+1] = squares[i][j];
        squares[i][j] = 0;
        if (j < grid_size-2) j += 1;
      } else {
        j--;
      }
    }
  }
  return squares_were_moved;
}

bool GameGrid::CompressDown() {
  bool squares_were_moved = false;
  for (int i=0; i<grid_size; i++) {
    for (int j=grid_size-2; j>=0; j--) {
      if (squares[i][j] > 0 && squares[i][j]==squares[i][j+1]) {
        squares_were_moved = true;
        squares[i][j+1] += 1;
        squares[i][j] = 0;
      }
    }
  }
  return squares_were_moved;
}

int GameGrid::getARandomSquare(int *i1, int *j1) {
  int empty_squares = CountEmptySquares();
  if (empty_squares < 1) return -1;
  int square1 = rand() % empty_squares;
  int counter = 0;
  for (int i=0; i<grid_size; i++) {
    for (int j=0; j<grid_size; j++) {
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

void GameGrid::StepLeft() {
  for (int i=1; i<grid_size; i++) {
    for (int j=0; j<grid_size; j++) {
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

int GameGrid::Value(int i, int j) {
  return 1 << squares[i][j];
}

int GameGrid::CountEmptySquares() {
  int result = 0;
  for (int i=0; i<grid_size; i++) {
    for (int j=0; j<grid_size; j++) {
      if (!(squares[i][j] > 0)) {
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
  for (int i=0; i<grid_size; i++) {
    for (int j=0; j<grid_size; j++) {
      squares[i][j] = 0;
    }
  }

  squares[0][0] = 1;
  squares[1][0] = 1;
}

GameGrid::~GameGrid() {
}

