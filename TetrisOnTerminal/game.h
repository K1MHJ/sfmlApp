#pragma once
#include "blocks.cpp"
#include "grid.h"

class Game {
public:
  Game();
  ~Game();
  void Draw();
  void HandleInput();
  void MoveBlockDown();
  bool gameOver;
  int score;
  bool gameTerminate;

private:
  void MoveBlockLeft();
  void MoveBlockRight();
  Block GetRandomBlock();
  std::vector<Block> GetAllBlocks();
  bool IsBlockOutside();
  void RotateBlock();
  void LockBlock();
  bool BlockFits();
  void Reset();
  void UpdateScore(int linesCleared, int moveDownPoints);
  Grid grid;
  std::vector<Block> blocks;
  Block currentBlock;
  Block nextBlock;
};
