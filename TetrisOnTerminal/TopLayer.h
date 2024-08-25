#pragma once

#include "SfmlPF.h"
#include <Events/KeyEvent.h>
#include <SFML/Graphics.hpp>
#include <random>
#include "grid.h"
#include "blocks.cpp"

#include "bot.h"

class TopLayer : public Layer {
public:
  TopLayer();
  virtual ~TopLayer() = default;

  virtual void OnAttach() override;
  virtual void OnDetach() override;

  void OnUpdate(Timestep ts) override;
  virtual void OnGuiRender() override;
  void OnEvent(Event &e) override;

private:
  sf::RenderWindow *m_window;
  bool OnKeyPressed(KeyPressedEvent &e);
  bool OnAppUpdate(AppUpdateEvent &e);
private:
  void MoveBlockRight();
  void MoveBlockLeft();
  void MoveBlockDown();
  void RotateBlock();

  Block GetRandomBlock();
  std::vector<Block> GetAllBlocks();
  bool IsBlockOutside();
  bool IsBlockOutside(Block& block);
  bool BlockFits();
  bool BlockFits(Block& block);
  void LockBlock();
  void Reset();
  Grid grid;
  std::vector<Block> blocks;
  Block currentBlock;
  Block nextBlock;
  
  bool gameOver;
  uint64_t m_LastUpdateTime;
  uint64_t m_Time[2];

  Bot m_bot;
  int m_count_used_block;
  std::mt19937 m_mt_for_block;
  char m_text[256];
  int m_score;
};
