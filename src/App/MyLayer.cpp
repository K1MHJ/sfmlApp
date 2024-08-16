#include "MyLayer.h"
#include <SFML/Graphics.hpp>

MyLayer::MyLayer() : Layer("MyLayer") {}

void MyLayer::OnAttach() {
  PROFILE_FUNCTION();

  // m_CheckerboardTexture =
  //Texture2D::Create("assets/textures/Checkerboard.png");
  //
  Application& app = Application::Get();
  m_window = static_cast<sf::RenderWindow*>(app.GetWindow().GetNativeWindow());
}

void MyLayer::OnDetach() { PROFILE_FUNCTION(); }

void MyLayer::OnUpdate(Timestep ts) {
  PROFILE_FUNCTION();

  // Update
  // m_CameraController.OnUpdate(ts);

  // Render
  m_window->clear(sf::Color::Red);
  // Renderer2D::ResetStats();
  {
    PROFILE_SCOPE("Renderer Prep");
    RenderCommand::SetClearColor(255, 200, 100);
    RenderCommand::Clear();
  }

  {
    static float rotation = 0.0f;
    rotation += ts * 50.0f;

    PROFILE_SCOPE("Renderer Draw");
    // Renderer2D::BeginScene(m_CameraController.GetCamera());
    // Renderer2D::DrawRotatedQuad({ 1.0f, 0.0f }, { 0.8f, 0.8f }, -45.0f, {
    // 0.8f, 0.2f, 0.3f, 1.0f }); Renderer2D::DrawQuad({ -1.0f, 0.0f }, { 0.8f,
    // 0.8f }, { 0.8f, 0.2f, 0.3f, 1.0f }); Renderer2D::DrawQuad({ 0.5f, -0.5f
    // }, { 0.5f, 0.75f }, m_SquareColor); Renderer2D::DrawQuad({ 0.0f, 0.0f,
    // -0.1f }, { 20.0f, 20.0f }, m_CheckerboardTexture, 10.0f);
    // Renderer2D::DrawRotatedQuad({ -2.0f, 0.0f, 0.0f }, { 1.0f, 1.0f },
    // rotation, m_CheckerboardTexture, 20.0f); Renderer2D::EndScene();

    // Renderer2D::BeginScene(m_CameraController.GetCamera());
    // for (float y = -5.0f; y < 5.0f; y += 0.5f)
    // {
    // 	for (float x = -5.0f; x < 5.0f; x += 0.5f)
    // 	{
    // 		glm::vec4 color = { (x + 5.0f) / 10.0f, 0.4f, (y + 5.0f)
    // / 10.0f, 0.7f }; 		Renderer2D::DrawQuad({ x, y }, { 0.45f, 0.45f }, color);
    // 	}
    // }
    // Renderer2D::EndScene();
  }
}

void MyLayer::OnGuiRender() {
  PROFILE_FUNCTION();

  // ImGui::Begin("Settings");

  // auto stats = Renderer2D::GetStats();
  //  ImGui::Text("Renderer2D Stats:");
  //  ImGui::Text("Draw Calls: %d", stats.DrawCalls);
  //  ImGui::Text("Quads: %d", stats.QuadCount);
  //  ImGui::Text("Vertices: %d", stats.GetTotalVertexCount());
  //  ImGui::Text("Indices: %d", stats.GetTotalIndexCount());

  // ImGui::ColorEdit4("Square Color", glm::value_ptr(m_SquareColor));
  // ImGui::End();
}

void MyLayer::OnEvent(Event &e) {
  // m_CameraController.OnEvent(e);
}
