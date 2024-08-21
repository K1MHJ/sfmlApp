#pragma once

#include "SfmlPF.h"
#include "Utils/PlatformUtils.h"
#include "block.h"
#include "grid.h"

class Bot {
public:
  void Init();
  void OnUpdate(Timestep ts);
  int Order(const Grid &_grid, Block &_curBlock, const Block &_nextBlock,
            int usedBlockCnt);
  void OnRender();
  void Reset();
  void GameOver();

private:
  bool gameOver;
  bool BlockFits(Block &block);
  bool IsBlockOutside(Block &block);
  bool SearchBestPlace(const Grid &_grid, const Block &_curBlock,
                       int &best_rotationState, int &best_colOffset);
  Grid m_grid;
  Block m_curBlock;
  Block m_forcastBlock;
  Block m_nextBlock;
  int m_lastCountUsedBlock;

  int m_bestColOffset;
  int m_bestRotState;
};
