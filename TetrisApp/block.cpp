#include "block.h"
#include <Renderer/Renderer2D.h>
#include <SfmlPF.h>

Block::Block() {
  cellSize = 30;
  rotationState = 0;
  colors = GetCellColors();
  rowOffset = 0;
  columnOffset = 0;
}
void Block::Draw(int offsetX, int offsetY) {
  std::vector<Position> tiles = GetCellPositions();
  for (auto &c : tiles) {
    Renderer2D::DrawFillRectangle(c.column * cellSize + offsetX,
                                  c.row * cellSize + offsetY, cellSize - 1,
                                  cellSize - 1, colors[id]);
  }
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
