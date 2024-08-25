#include "block.h"
#include <ncurses.h>

extern WINDOW *win;

Block::Block() {
  cellSize = 30;
  rotationState = 0;
  colors = GetCellColors();
  rowOffset = 0;
  columnOffset = 0;
}
void Block::Draw(int offsetX, int offsetY) {
  wattron(win, COLOR_PAIR(10 + id));
  std::vector<Position> tiles = GetCellPositions();
  for (auto &c : tiles) {
    mvwprintw(win, c.row + offsetY, c.column + offsetX, " ");
  }
  wattroff(win, COLOR_PAIR(10 + id));
}
void Block::Move(int row, int column) {
  rowOffset += row;
  columnOffset += column;
}
std::vector<Position> Block::GetCellPositions() {
  std::vector<Position> tiles = cells[rotationState];
  std::vector<Position> movedTiles;
  for (Position &item : tiles) {
    Position newPos =
        Position(item.row + rowOffset, item.column + columnOffset);
    movedTiles.push_back(newPos);
  }
  return movedTiles;
}

void Block::Rotate() {
  rotationState++;
  if (rotationState == (int)cells.size()) {
    rotationState = 0;
  }
}

void Block::UndoRotation() {
  rotationState--;
  if (rotationState == -1) {
    rotationState = cells.size() - 1;
  }
}
