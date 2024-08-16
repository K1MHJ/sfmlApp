#pragma once

#include "RenderCommand.h"

class Renderer {
public:
  static void Init();
  static void Shutdown();

  static void OnWindowResize(uint32_t width, uint32_t height);

  static void BeginScene();
  static void EndScene();

  static RendererAPI::API GetAPI() { return RendererAPI::GetAPI(); }

private:
  struct SceneData {
    glm::mat4 ViewProjectionMatrix;
  };

  static Scope<SceneData> s_SceneData;
};
