#pragma once

#include "SfmlPF.h"
#include <SFML/Graphics.hpp>
#include <Events/KeyEvent.h>

class MyLayer : public Layer {
public:
  MyLayer();
  virtual ~MyLayer() = default;

  virtual void OnAttach() override;
  virtual void OnDetach() override;

  void OnUpdate(Timestep ts) override;
  virtual void OnGuiRender() override;
  void OnEvent(Event &e) override;

private:
  sf::RenderWindow* m_window;
  bool OnKeyPressed(KeyPressedEvent &e);


private:
  float x,y;
};
