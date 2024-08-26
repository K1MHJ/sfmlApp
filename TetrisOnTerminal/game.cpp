#include "game.h"
#include <fcntl.h>
#include <iostream>
#include <ncurses.h>
#include <stdio.h>
#include <termios.h>
#include <unistd.h>

extern WINDOW *win;

int GetKeyPressed(void) {
  struct termios oldt, newt;
  int ch;
  int oldf;

  tcgetattr(STDIN_FILENO, &oldt);
  newt = oldt;
  newt.c_lflag &= ~(ICANON | ECHO);
  tcsetattr(STDIN_FILENO, TCSANOW, &newt);
  oldf = fcntl(STDIN_FILENO, F_GETFL, 0);
  fcntl(STDIN_FILENO, F_SETFL, oldf | O_NONBLOCK);
  ch = getchar();
  tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
  fcntl(STDIN_FILENO, F_SETFL, oldf);
  if (ch != EOF) {
    ungetc(ch, stdin);
    return 1;
  }
  return 0;
}

Game::Game() {
  grid = Grid();
  blocks = GetAllBlocks();
  currentBlock = GetRandomBlock();
  nextBlock = GetRandomBlock();
  gameOver = false;
  score = 0;
  gameTerminate = false;
}

Game::~Game() {}

Block Game::GetRandomBlock() {
  if (blocks.empty()) {
    blocks = GetAllBlocks();
  }
  int randomIndex = rand() % blocks.size();
  Block block = blocks[randomIndex];
  blocks.erase(blocks.begin() + randomIndex);
  return block;
}

std::vector<Block> Game::GetAllBlocks() {
  return {IBlock(), JBlock(), LBlock(), OBlock(), SBlock(), TBlock(), ZBlock()};
}

void Game::Draw() {
  grid.Draw();
  currentBlock.Draw(2, 4);

  wattron(win, COLOR_PAIR(0));
  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 4; j++) {
      mvwprintw(win, 8 + i, 33 + j, " ");
    }
  }
  switch (nextBlock.id) {
  case 3:
    nextBlock.Draw(30, 8);
    break;
  case 4:
    nextBlock.Draw(30, 8);
    break;
  default:
    nextBlock.Draw(30, 8);
    break;
  }
}

void Game::HandleInput() {
  int keyPressed = GetKeyPressed();
  if (gameOver && keyPressed != 0) {
    gameOver = false;
    Reset();
  }
  if (!gameOver && keyPressed != 0) {
    switch (getchar()) {
    case 'a':
      MoveBlockLeft();
      break;
    case 'd':
      MoveBlockRight();
      break;
    case 's':
      MoveBlockDown();
      UpdateScore(0, 1);
      break;
    case 'w':
      RotateBlock();
      break;
    case 'q':
      gameTerminate = true;
      return;
    }
  }
  AutoDecision();
}

void Game::MoveBlockLeft() {
  if (!gameOver) {
    currentBlock.Move(0, -1);
    if (IsBlockOutside() || BlockFits() == false) {
      currentBlock.Move(0, 1);
    }
  }
}

void Game::MoveBlockRight() {
  if (!gameOver) {
    currentBlock.Move(0, 1);
    if (IsBlockOutside() || BlockFits() == false) {
      currentBlock.Move(0, -1);
    }
  }
}

void Game::MoveBlockDown() {
  if (!gameOver) {
    currentBlock.Move(1, 0);
    if (IsBlockOutside() || BlockFits() == false) {
      currentBlock.Move(-1, 0);
      LockBlock();
    }
  }
}

bool Game::IsBlockOutside() {
  std::vector<Position> tiles = currentBlock.GetCellPositions();
  for (Position item : tiles) {
    if (grid.IsCellOutside(item.row, item.column)) {
      return true;
    }
  }
  return false;
}

void Game::RotateBlock() {
  if (!gameOver) {
    currentBlock.Rotate();
    if (IsBlockOutside() || BlockFits() == false) {
      currentBlock.UndoRotation();
    } else {
      // PlaySound(rotateSound);
    }
  }
}

void Game::LockBlock() {
  std::vector<Position> tiles = currentBlock.GetCellPositions();
  for (Position item : tiles) {
    grid.grid[item.row][item.column] = currentBlock.id;
  }
  currentBlock = nextBlock;
  if (BlockFits() == false) {
    gameOver = true;
  }
  nextBlock = GetRandomBlock();
  int rowsCleared = grid.ClearFullRows();
  if (rowsCleared > 0) {
    UpdateScore(rowsCleared, 0);
  }
}

bool Game::BlockFits() {
  std::vector<Position> tiles = currentBlock.GetCellPositions();
  for (Position item : tiles) {
    if (grid.IsCellEmpty(item.row, item.column) == false) {
      return false;
    }
  }
  return true;
}

void Game::Reset() {
  grid.Initialize();
  blocks = GetAllBlocks();
  currentBlock = GetRandomBlock();
  nextBlock = GetRandomBlock();
  score = 0;
  gameTerminate = false;
}

void Game::UpdateScore(int linesCleared, int moveDownPoints) {
  score += linesCleared;
}
void Game::AutoDecision() {
  std::vector<Block> bblk = GetBottomBlocks();
  double max_score = -10000000000.0;
  Block best_blk = currentBlock;
  for (auto &b : bblk) {
    Grid tmpGrid = grid;
    std::vector<Position> tiles = b.GetCellPositions();
    for (auto &t : tiles) {
      tmpGrid.grid[t.row][t.column] = b.id;
    }
    double s = ScoreTotal(tmpGrid);
    if (max_score < s) {
      max_score = s;
      best_blk = b;
    }
  }
  if (best_blk.RotationState() != currentBlock.RotationState()) {
    RotateBlock();
  } else {
    if (best_blk.ColumnOffset() != currentBlock.ColumnOffset()) {
      if (best_blk.ColumnOffset() < currentBlock.ColumnOffset()) {
        MoveBlockLeft();
      } else {
        MoveBlockRight();
      }
    }
  }
}

double Game::ScoreTotal(const Grid &_grid) {
  double a, b, c, d;
  double s;
  a = -0.510066;
  b = 0.760666;
  c = -0.35663;
  d = -0.184483;
  s = a * ScoreAggregateHeight(_grid);
  s += b * ScoreCompleteLines(_grid);
  s += c * ScoreHoles(_grid);
  s += d * ScoreBumpiness(_grid);
  return s;
}
int Game::ScoreAggregateHeight(const Grid &_grid) {
  int total = 0;
  for (int c = 0; c < _grid.Column(); c++) {
    for (int r = 0; r < _grid.Row(); r++) {
      if (!_grid.IsCellEmpty(r, c)) {
        total += (_grid.Row() - r);
        break;
      }
    }
  }
  return total;
}
int Game::ScoreCompleteLines(const Grid &_grid) {
  int total = 0;
  for (int r = 0; r < _grid.Row(); r++) {
    bool complete = true;
    for (int c = 0; c < _grid.Column(); c++) {
      if (_grid.IsCellEmpty(r, c)) {
        complete = false;
        break;
      }
    }
    if (complete) {
      total++;
    }
  }
  return total;
}
int Game::ScoreHoles(const Grid &_grid) {
  int total = 0;
  for (int c = 0; c < _grid.Column(); c++) {
    for (int r = 0; r < _grid.Row(); r++) {
      if (!_grid.IsCellEmpty(r, c)) {
        for (int i = r + 1; i < _grid.Row(); i++) {
          if (_grid.IsCellEmpty(i, c)) {
            total++;
          }
        }
      }
    }
  }
  return total;
}
int Game::ScoreBumpiness(const Grid &_grid) {
  int total = 0;
  std::vector<int> height(0, _grid.Column());
  for (int c = 0; c < _grid.Column(); c++) {
    for (int r = 0; r < _grid.Row(); r++) {
      if (!_grid.IsCellEmpty(r, c)) {
        height[c] = _grid.Row() - r;
        break;
      }
    }
  }
  for (int h = 1; h < height.size(); h++) {
    total += abs(height[h - 1] - height[h]);
  }
  return total;
}
std::vector<Block> Game::GetBottomBlocks() {
  std::vector<Block> bottom_blocks;
  Block curblk = currentBlock;
  Block blk = currentBlock;
  int best_coloffset;
  int best_rotate;
  int MIN_EMPTY = grid.Column() * grid.Row();
  for (int r = 0; r < blk.MaxRotationState(); ++r) {
    currentBlock = blk;
    int _r = r;
    while (_r-- > 0) {
      currentBlock.Rotate();
    }
    while (!(IsBlockOutside() || BlockFits() == false)) {
      currentBlock.Move(0, -1);
    }
    Block tblk = currentBlock;
    for (;;) {
      tblk.Move(0, 1);
      currentBlock = tblk;
      if (IsBlockOutside() || BlockFits() == false) {
        break;
      }
      while (!(IsBlockOutside() || BlockFits() == false)) {
        currentBlock.Move(1, 0);
      }
      currentBlock.Move(-1, 0);
      bottom_blocks.emplace_back(currentBlock);
    }
  }
  currentBlock = curblk;
  return bottom_blocks;
}
