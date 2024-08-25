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
      // CORE_INFO("BEST: '{0}', '{1}'", m_bestColOffset, m_bestRotState);
    }
    if (m_bestRotState != _curBlock.RotationState()) {
      // CORE_INFO("Rotate");
      return 3;
    } else {
      if (m_bestColOffset != _curBlock.ColumnOffset()) {
        if (m_bestColOffset < _curBlock.ColumnOffset()) {
          // CORE_INFO("Left");
          return 2;
        } else {
          // CORE_INFO("Right");
          return 1;
        }
      }
    }
  }
  return 0;
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
std::vector<Block> Bot::GetBottomBlocks(const Grid &_grid,
                                        const Block &_curBlock) {
  std::vector<Block> bottom_blocks;
  Block blk = _curBlock;
  int best_coloffset;
  int best_rotate;
  int MIN_EMPTY = _grid.Column() * _grid.Row();
  m_grid = _grid;
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
      bottom_blocks.emplace_back(bottomBlk);
    }
  }
  return bottom_blocks;
}

std::vector<Position> Bot::GetLegalSidePosition(const Grid &_grid,
                                                Position pos) {
  std::vector<Position> bsp;
  for (int i = 0; i < 4; i++) {
    Position sp = pos;
    switch (i) {
    case 0:
      sp.row++;
      break;
    case 1:
      sp.row--;
      break;
    case 2:
      sp.column++;
      break;
    case 3:
      sp.column--;
      break;
    default:
      break;
    }
    if (0 <= sp.column && sp.column < _grid.Column() && 0 <= sp.row &&
        sp.row < _grid.Row()) {
      bsp.emplace_back(sp);
    }
  }
  return bsp;
}
bool Bot::SearchBestPlace(const Grid &_grid, const Block &_curBlock,
                          int &best_rotationState, int &best_colOffset) {
  std::vector<Block> blks = GetBottomBlocks(_grid, _curBlock);
  int max_clearRowCount = 0;
  int max_contackPoint = 0;
  Block best_block;
  best_rotationState = _curBlock.RotationState();
  best_colOffset = _curBlock.ColumnOffset();
  for (auto &blk : blks) {
    Grid tmp_grid = _grid;
    std::vector<Position> tiles = blk.GetCellPositions();
    for (Position item : tiles) {
      tmp_grid.grid[item.row][item.column] = blk.id;
    }
    int cr = tmp_grid.ClearFullRows();
    if (max_clearRowCount < cr) {
      max_clearRowCount = cr;
      best_block = blk;
    }
  }
  if (max_clearRowCount > 0) {
    best_rotationState = best_block.RotationState();
    best_colOffset = best_block.ColumnOffset();
    return true;
  }

  for (auto &blk : blks) {
    Grid tmp_grid = _grid;
    std::vector<Position> tiles = blk.GetCellPositions();
    int contact_point = 0;
    for (Position item : tiles) {
      std::vector<Position> legal_positions =
          GetLegalSidePosition(tmp_grid, item);
      if (item.row == tmp_grid.Row() - 1) {
        contact_point++;
      }
      if (item.column == 0 || item.column == tmp_grid.Column() - 1) {
        contact_point++;
      }
      for (auto &p : legal_positions) {
        if (tmp_grid.grid[p.row][p.column] != 0) {
          contact_point+=1;
        }
      }
    }
    if (max_contackPoint < contact_point) {
      max_contackPoint = contact_point;
      best_block = blk;
    }
  }
  if (max_contackPoint > 0) {
    best_rotationState = best_block.RotationState();
    best_colOffset = best_block.ColumnOffset();
    return true;
  }
  return false;
}
