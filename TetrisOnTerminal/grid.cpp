#include "grid.h"
#include "colors.h"
#include <ncurses.h>

extern WINDOW *win;

Grid::Grid() {
  numRows = 20;
  numCols = 10;
  cellSize = 30;
  Initialize();
  colors = GetCellColors();
}
Grid::~Grid() {}

void Grid::Initialize() {
  for (int row = 0; row < numRows; ++row) {
    for (int col = 0; col < numCols; ++col) {
      grid[row][col] = 0;
    }
  }
}
void Grid::Draw() const {
  for (int col = -1; col < numCols + 1; ++col) {
    if (col != -1 && col != numCols) {
      mvwprintw(win, 2, col + 2, "%d", col);
    }
    mvwprintw(win, 3, col + 2, "#");
    mvwprintw(win, 4 + numRows, col + 2, "#");
  }
  for (int row = 0; row < numRows; ++row) {
    mvwprintw(win, row + 4, 3 + numCols, "%d", row);
    mvwprintw(win, row + 4, 1, "#");
    mvwprintw(win, row + 4, 2 + numCols, "#");
  }
  for (int row = 0; row < numRows; ++row) {
    for (int col = 0; col < numCols; ++col) {
      int cellValue = grid[row][col];
      wattron(win, COLOR_PAIR(10 + cellValue));
      mvwprintw(win, row + 4, col + 2, " ");
      wattroff(win, COLOR_PAIR(10 + cellValue));
    }
  }
}

bool Grid::IsCellOutside(int row, int column) const {
  if (row >= 0 && row < numRows && column >= 0 && column < numCols) {
    return false;
  }
  return true;
}

bool Grid::IsCellEmpty(int row, int column) const {
  if (grid[row][column] == 0) {
    return true;
  }
  return false;
}

int Grid::ClearFullRows() {
  int completed = 0;
  for (int row = numRows - 1; row >= 0; row--) {
    if (IsRowFull(row)) {
      ClearRow(row);
      completed++;
    } else if (completed > 0) {
      MoveRowDown(row, completed);
    }
  }
  return completed;
}

bool Grid::IsRowFull(int row) {
  for (int column = 0; column < numCols; column++) {
    if (grid[row][column] == 0) {
      return false;
    }
  }
  return true;
}

void Grid::ClearRow(int row) {
  for (int column = 0; column < numCols; column++) {
    grid[row][column] = 0;
  }
}

void Grid::MoveRowDown(int row, int numRows) {
  for (int column = 0; column < numCols; column++) {
    grid[row + numRows][column] = grid[row][column];
    grid[row][column] = 0;
  }
}
