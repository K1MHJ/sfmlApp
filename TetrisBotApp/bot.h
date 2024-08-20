#pragma once

#include "SfmlPF.h"
#include "Utils/PlatformUtils.h"
#include "grid.h"
#include "block.h"

class Bot
{
public:
  void Init();
  void OnUpdate(Timestep ts);
  int Order(const Grid& _grid, Block& _curBlock, const Block& _nextBlock);
  void OnRender();
  void Reset();
  void GameOver();
private:
  bool gameOver;
  bool BlockFits(Block& block);
  bool IsBlockOutside(Block &block);
  Grid m_grid;
  Block m_curBlock;
  Block m_forcastBlock;
  Block m_nextBlock;
};
