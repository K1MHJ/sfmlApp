#include "TopLayer.h"
#include "Renderer/Renderer2D.h"
#include "Utils/PlatformUtils.h"
#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>
#include <vector>


TopLayer::TopLayer() : Layer("TopLayer") {
  grid = Grid();
  blocks = GetAllBlocks();
  currentBlock = GetRandomBlock();
  nextBlock = GetRandomBlock();
  gameOver = false;
  m_LastUpdateTime = 0;
}

Block TopLayer::GetRandomBlock() {
  if (blocks.empty()) {
    blocks = GetAllBlocks();
  }
  int randomIndex = m_mt_for_block() % blocks.size();
  Block block = blocks[randomIndex];
  blocks.erase(blocks.begin() + randomIndex);
  return block;
}

std::vector<Block> TopLayer::GetAllBlocks() {
  return {IBlock(), JBlock(), LBlock(), OBlock(), SBlock(), TBlock(), ZBlock()};
}

bool TopLayer::OnAppUpdate(AppUpdateEvent &e) {
  MoveBlockDown();
  return true;
}
bool TopLayer::OnKeyPressed(KeyPressedEvent &e) {
  switch (e.GetKeyCode()) {
  case sf::Keyboard::D:
    MoveBlockRight();
    break;
  case sf::Keyboard::A:
    MoveBlockLeft();
    break;
  case sf::Keyboard::W:
    RotateBlock();
    break;
  case sf::Keyboard::S:
    MoveBlockDown();
    m_Time[1] = 0;
    break;
  case sf::Keyboard::R:
    gameOver = false;
    Reset();
    break;
  }
  return true;
}

void TopLayer::OnAttach() {
  PROFILE_FUNCTION();
  Application &app = Application::Get();
  m_window = static_cast<sf::RenderWindow *>(app.GetWindow().GetNativeWindow());
  Renderer2D::Init(m_window);
  Reset();
  CORE_INFO("Attach");
  Renderer2D::Clear(0, 0, 0);
  m_bot.Init();
}

void TopLayer::OnDetach() { PROFILE_FUNCTION(); }

void TopLayer::OnUpdate(Timestep ts) {
  PROFILE_FUNCTION();
  m_Time[0] += ts.GetMilliseconds();
  m_Time[1] += ts.GetMilliseconds();
  if (gameOver) {
    m_bot.GameOver();
  }
  if (m_Time[0] > 30) {
    m_Time[0] = m_Time[0] % 30;
    Renderer2D::Clear(0, 0, 0);
    Renderer2D::BeginScene();
    grid.Draw();
    currentBlock.Draw(11, 11);
    nextBlock.Draw(270, 270);
    m_bot.OnRender();
    snprintf(m_text,256,"Blocks : %d", m_count_used_block);
    Renderer2D::DrawText(m_text, 330, 11, 30, sf::Color::Yellow);
    if (gameOver) {
      Renderer2D::DrawText("GAME OVER", 130, 200, 60, sf::Color::Red);
    }
    Renderer2D::EndScene();
  }
  if (m_Time[1] > 5) {
    m_Time[1] = m_Time[1] % 50;
    if (!gameOver) {
      AppUpdateEvent e;
      Application::Get().OnEvent(e);
      int order = 0;
      order = m_bot.Order((const Grid &)grid, currentBlock,
                          (const Block &)nextBlock, m_count_used_block);
      switch (order) {
      case 0:
        break;
      case 1:
        MoveBlockRight();
        break;
      case 2:
        MoveBlockLeft();
        break;
      case 3:
        RotateBlock();
        break;
      }
    }
  }
}

void TopLayer::OnGuiRender() { PROFILE_FUNCTION(); }

void TopLayer::OnEvent(Event &e) {
  EventDispatcher dispatcher(e);
  dispatcher.Dispatch<KeyPressedEvent>(BIND_EVENT_FN(OnKeyPressed));
  dispatcher.Dispatch<AppUpdateEvent>(BIND_EVENT_FN(OnAppUpdate));
}

void TopLayer::MoveBlockRight() {
  if (!gameOver) {
    currentBlock.Move(0, 1);
    if (IsBlockOutside() || BlockFits() == false) {
      currentBlock.Move(0, -1);
    }
  }
}
void TopLayer::MoveBlockLeft() {
  if (!gameOver) {
    currentBlock.Move(0, -1);
    if (IsBlockOutside() || BlockFits() == false) {
      currentBlock.Move(0, 1);
    }
  }
}
void TopLayer::MoveBlockDown() {
  if (!gameOver) {
    currentBlock.Move(1, 0);
    if (IsBlockOutside() || BlockFits() == false) {
      currentBlock.Move(-1, 0);
      LockBlock();
    }
  }
}

bool TopLayer::IsBlockOutside() {
  std::vector<Position> tiles = currentBlock.GetCellPositions();
  for (Position item : tiles) {
    if (grid.IsCellOutside(item.row, item.column)) {
      return true;
    }
  }
  return false;
}

bool TopLayer::IsBlockOutside(Block &block) {
  std::vector<Position> tiles = block.GetCellPositions();
  for (Position item : tiles) {
    if (grid.IsCellOutside(item.row, item.column)) {
      return true;
    }
  }
  return false;
}
void TopLayer::RotateBlock() {
  if (!gameOver) {
    currentBlock.Rotate();
    if (IsBlockOutside() || BlockFits() == false) {
      currentBlock.UndoRotation();
    } else {
      // PlaySound(rotateSound);
    }
  }
}

void TopLayer::LockBlock() {
  std::vector<Position> tiles = currentBlock.GetCellPositions();
  for (Position item : tiles) {
    grid.grid[item.row][item.column] = currentBlock.id;
  }
  currentBlock = nextBlock;
  m_count_used_block++;
  if(m_count_used_block >= 20){
    gameOver = true;
  }
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

bool TopLayer::BlockFits() {
  std::vector<Position> tiles = currentBlock.GetCellPositions();
  for (Position item : tiles) {
    if (grid.IsCellEmpty(item.row, item.column) == false) {
      return false;
    }
  }
  return true;
}

bool TopLayer::BlockFits(Block &block) {
  std::vector<Position> tiles = block.GetCellPositions();
  for (Position item : tiles) {
    if (grid.IsCellEmpty(item.row, item.column) == false) {
      return false;
    }
  }
  return true;
}
void TopLayer::Reset() {
  grid.Initialize();
  blocks = GetAllBlocks();
  currentBlock = GetRandomBlock();
  nextBlock = GetRandomBlock();
  m_count_used_block = 1;
}
