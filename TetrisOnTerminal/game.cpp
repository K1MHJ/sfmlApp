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
  currentBlock.Draw(1, 2);

  wattron(win, COLOR_PAIR(0));
  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 4; j++) {
      // mvwdelch(win, 8+i , 33+j);
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
  if (keyPressed != 0) {
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
      break;
    }
  }
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
    // PlaySound(clearSound);
    // UpdateScore(rowsCleared, 0);
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
  switch (linesCleared) {
  case 1:
    score += 100;
    break;
  case 2:
    score += 300;
    break;
  case 3:
    score += 500;
    break;
  default:
    break;
  }

  score += moveDownPoints;
}
