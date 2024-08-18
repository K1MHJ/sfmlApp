#include "pch.h"
#include "Renderer.h"

Scope<Renderer::SceneData> Renderer::s_SceneData = CreateScope<Renderer::SceneData>();

void Renderer::Init()
{
  RenderCommand::Init();

  //Renderer2D::Init();
}

void Renderer::Shutdown()
{
  //Renderer2D::Shutdown();
}

void Renderer::OnWindowResize(uint32_t width, uint32_t height)
{
  RenderCommand::SetViewport(0, 0, width, height);
}

void Renderer::BeginScene()
{
  //s_SceneData->ViewProjectionMatrix = camera.GetViewProjectionMatrix();
}
void Renderer::EndScene()
{
}
