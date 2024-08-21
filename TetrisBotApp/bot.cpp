#include "bot.h"
#include "blocks.cpp"
#include <map>
#include <unordered_set>

enum class BlockType {
  IBlock,
  JBlock,
  LBlock,
  OBlock,
  SBlock,
  TBlock,
  ZBlock,
  NONE
};
BlockType BlockType(Block &block) {
  if (block.id == IBlock().id) {
    return BlockType::IBlock;
  } else if (block.id == JBlock().id) {
    return BlockType::JBlock;
  } else if (block.id == LBlock().id) {
    return BlockType::LBlock;
  } else if (block.id == OBlock().id) {
    return BlockType::OBlock;
  } else if (block.id == SBlock().id) {
    return BlockType::SBlock;
  } else if (block.id == TBlock().id) {
    return BlockType::TBlock;
  } else if (block.id == ZBlock().id) {
    return BlockType::ZBlock;
  }
  return BlockType::NONE;
}
void Bot::Init() {
  gameOver = false;
  m_lastCountUsedBlock = 0;
}
void Bot::OnUpdate(Timestep ts) {}
void Bot::OnRender() { m_forcastBlock.Draw(11, 11); }
void Bot::Reset() {}
void Bot::GameOver() { gameOver = true; }
int Bot::Order(const Grid &_grid, Block &_curBlock, const Block &_nextBlock,
               int usedBlockCnt) {
  if (!gameOver) {
    if (m_lastCountUsedBlock != usedBlockCnt) {
      m_lastCountUsedBlock = usedBlockCnt;
      m_grid = _grid;
      SearchBestPlace(_grid, _curBlock, m_bestRotState, m_bestColOffset);
      CORE_INFO("BEST: '{0}', '{1}'", m_bestColOffset, m_bestRotState);
    }
    if (m_bestRotState != _curBlock.RotationState()) {
      CORE_INFO("Rotate");
      return 3;
    } else {
      if (m_bestColOffset != _curBlock.ColumnOffset()) {
        if (m_bestColOffset < _curBlock.ColumnOffset()) {
          CORE_INFO("Left");
          return 2;
        } else {
          CORE_INFO("Right");
          return 1;
        }
      }
    }
    return 0;
  }
}

bool Bot::BlockFits(Block &block) {
  std::vector<Position> tiles = block.GetCellPositions();
  for (Position item : tiles) {
    if (m_grid.IsCellEmpty(item.row, item.column) == false) {
      return false;
    }
  }
  return true;
}

bool Bot::IsBlockOutside(Block &block) {
  std::vector<Position> tiles = block.GetCellPositions();
  for (Position item : tiles) {
    if (m_grid.IsCellOutside(item.row, item.column)) {
      return true;
    }
  }
  return false;
}

bool Bot::SearchBestPlace(const Grid &_grid, const Block &_curBlock,
                          int &best_rotationState, int &best_colOffset) {
  Block blk = _curBlock;
  int best_coloffset;
  int best_rotate;
  int MIN_EMPTY = _grid.Column() * _grid.Row();
  for (int r = 0; r < blk.MaxRotationState(); ++r) {
    Block rblk = blk;
    int _r = r;
    while (_r-- > 0) {
      rblk.Rotate();
    }
    while (!(IsBlockOutside(rblk) || BlockFits(rblk) == false)) {
      rblk.Move(0, -1);
    }
    for (;;) {
      rblk.Move(0, 1);
      if (IsBlockOutside(rblk) || BlockFits(rblk) == false) {
        break;
      }
      Block bottomBlk = rblk;
      while (!(IsBlockOutside(bottomBlk) || BlockFits(bottomBlk) == false)) {
        bottomBlk.Move(1, 0);
      }
      bottomBlk.Move(-1, 0);

      std::vector<Position> tiles = bottomBlk.GetCellPositions();
      std::map<int, int> blockoccupiedrow;
      for (Position item : tiles) {
        if (!blockoccupiedrow.contains(item.row)) {
          blockoccupiedrow[item.row] = 0;
        }
        blockoccupiedrow[item.row]++;
      }
      int emptycnt = 0;
      for (const auto &it : blockoccupiedrow) {
        for (int c = 0; c < _grid.Column(); c++) {
          if (_grid.IsCellEmpty(it.first, c)) {
            emptycnt++;
          }
        }
        emptycnt -= it.second;
      }
      if (emptycnt < MIN_EMPTY) {
        MIN_EMPTY = emptycnt;
        best_coloffset = rblk.ColumnOffset();
        best_rotate = rblk.RotationState();
      }
    }
  }
  best_rotationState = best_rotate;
  best_colOffset = best_coloffset;
  return true;
}
