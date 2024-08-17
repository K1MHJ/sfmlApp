#include "MyLayer.h"
#include "Renderer/Renderer2D.h"
#include <SFML/Graphics.hpp>
#include <iostream>

MyLayer::MyLayer() : Layer("MyLayer"), x(0), y(0) {}

bool MyLayer::OnKeyPressed(KeyPressedEvent &e) {
  switch (e.GetKeyCode()) {
  case sf::Keyboard::D:
    x += 10;
    break;
  case sf::Keyboard::A:
    x -= 10;
    break;
  case sf::Keyboard::W:
    y -= 10;
    break;
  case sf::Keyboard::S:
    y += 10;
    break;
  }
  return true;
}

void MyLayer::OnAttach() {
  PROFILE_FUNCTION();
  Application &app = Application::Get();
  m_window = static_cast<sf::RenderWindow *>(app.GetWindow().GetNativeWindow());
  Renderer2D::Init(m_window);
}

void MyLayer::OnDetach() { PROFILE_FUNCTION(); }

void MyLayer::OnUpdate(Timestep ts) {
  PROFILE_FUNCTION();
  // Update

  // Render
  m_window->clear(sf::Color::Blue);
  // Renderer2D::ResetStats();
  {
    PROFILE_SCOPE("Renderer Prep");
    RenderCommand::SetClearColor(255, 200, 100);
    RenderCommand::Clear();
  }

  PROFILE_SCOPE("Renderer Draw");
  Renderer2D::BeginScene();
  Renderer2D::DrawCircle(50, x, y, Color{100, 100, 100});
  Renderer2D::EndScene();
}

void MyLayer::OnGuiRender() { PROFILE_FUNCTION(); }

void MyLayer::OnEvent(Event &e) {
  EventDispatcher dispatcher(e);
  dispatcher.Dispatch<KeyPressedEvent>(BIND_EVENT_FN(OnKeyPressed));
}
