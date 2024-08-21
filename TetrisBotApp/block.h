#pragma once
#include "colors.h"
#include "position.h"
#include <map>
#include <vector>

class Block {
public:
  Block();
  void Draw(int offsetX, int offsetY);
  void Move(int rows, int columns);
  void Rotate();
  void UndoRotation();
  int id;
  std::map<int, std::vector<Position>> cells;
  std::vector<Position> GetCellPositions();
  int RowOffset() const { return rowOffset; }
  int ColumnOffset() const { return columnOffset; }
  int RotationState() const { return rotationState; }
  int MaxRotationState() const { return cells.size(); }

private:
  int rowOffset;
  int columnOffset;
  int cellSize;
  int rotationState;
  std::vector<Color> colors;
};
