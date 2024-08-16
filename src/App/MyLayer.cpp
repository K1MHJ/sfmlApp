#include "MyLayer.h"
#include <SFML/Graphics.hpp>
#include "Renderer/Renderer2D.h"

MyLayer::MyLayer() : Layer("MyLayer") {}

void MyLayer::OnAttach() {
  PROFILE_FUNCTION();

  // m_CheckerboardTexture =
  //Texture2D::Create("assets/textures/Checkerboard.png");
  //
  Application& app = Application::Get();
  m_window = static_cast<sf::RenderWindow*>(app.GetWindow().GetNativeWindow());
  Renderer2D::Init(m_window);
}

void MyLayer::OnDetach() { PROFILE_FUNCTION(); }

void MyLayer::OnUpdate(Timestep ts) {
  PROFILE_FUNCTION();

  // Update
  // m_CameraController.OnUpdate(ts);

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
  Renderer2D::DrawCircle();
  Renderer2D::EndScene();
}

void MyLayer::OnGuiRender() {
  PROFILE_FUNCTION();
}

void MyLayer::OnEvent(Event &e) {
}
