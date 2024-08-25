#pragma once
#include "colors.h"
#include <vector>

class Grid {
public:
  Grid();
  ~Grid();
  void Initialize();
  void Draw()const;
  bool IsCellOutside(int row, int column) const;
  bool IsCellEmpty(int row, int column) const;
  int ClearFullRows();
  int Row() const{return numRows;}
  int Column() const{return numCols;}
  int grid[20][10];

private:
  bool IsRowFull(int row);
  void ClearRow(int row);
  void MoveRowDown(int row, int numRows);
  int numRows;
  int numCols;
  int cellSize;
  std::vector<Color> colors;
};
