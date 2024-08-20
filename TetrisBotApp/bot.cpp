#include "bot.h"
#include "blocks.cpp"
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
void Bot::Init() { gameOver = false; }
void Bot::OnUpdate(Timestep ts) {}
void Bot::OnRender() {
  m_forcastBlock.Draw(11,11);
}
void Bot::Reset() {}
void Bot::GameOver() { gameOver = true; }
int Bot::Order(const Grid &_grid, Block &_curBlock, const Block &_nextBlock) {
  if (!gameOver) {
    m_grid = _grid;
    m_forcastBlock = m_curBlock = _curBlock;
    m_forcastBlock.id = 8;
    m_nextBlock = _nextBlock;
    // auto t = BlockType(_curBlock);
    //while(IsBlockOutside(m_forcastBlock) || BlockFits(m_forcastBlock) == false)
    {
      //m_forcastBlock.Move(1, 0);
    }
    //m_forcastBlock.Move(-1, 0);
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
// void Bot::MoveBlockDown() {
//   if (!gameOver) {
//     currentBlock.Move(1, 0);
//     if (IsBlockOutside() || BlockFits() == false) {
//       currentBlock.Move(-1, 0);
//       LockBlock();
//     }
//   }
// }

// void Bot::LockBlock() {
//   std::vector<Position> tiles = currentBlock.GetCellPositions();
//   for (Position item : tiles) {
//     grid.grid[item.row][item.column] = currentBlock.id;
//   }
//   currentBlock = nextBlock;
//   if (BlockFits() == false) {
//     gameOver = true;
//   }
//   nextBlock = GetRandomBlock();
//   int rowsCleared = grid.ClearFullRows();
//   if (rowsCleared > 0) {
//     // PlaySound(clearSound);
//     // UpdateScore(rowsCleared, 0);
//   }
// }
