#pragma once

#include "SfmlPF.h"
#include <Events/KeyEvent.h>
#include <SFML/Graphics.hpp>

#include "grid.h"
#include "blocks.cpp"

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
  void LockBlock();
  bool BlockFits();
  void Reset();
  Grid grid;
  std::vector<Block> blocks;
  Block currentBlock;
  Block nextBlock;
  
  bool gameOver;
  uint64_t m_LastUpdateTime;
};
