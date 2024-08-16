#include "SfmlRendererAPI.h"
#include "pch.h"
#include <SFML/Graphics.hpp>

SFMLRendererAPI::SFMLRendererAPI() {
  CORE_ASSERT(windowHandle, "Window handle is null");
}

void SFMLRendererAPI::Init() {}

void SFMLRendererAPI::SetViewport(uint32_t x, uint32_t y, uint32_t width,
                                  uint32_t height) {}

void SFMLRendererAPI::SetClearColor(uint8_t red, uint8_t green, uint8_t blue) {
  m_red = red;
  m_green = green;
  m_blue = blue;
}

void SFMLRendererAPI::Clear() {}

// void SFMLRendererAPI::DrawIndexed(const Ref<VertexArray>& vertexArray,
// uint32_t indexCount)
// {
//   vertexArray->Bind();
//   uint32_t count = indexCount ? indexCount :
//   vertexArray->GetIndexBuffer()->GetCount(); glDrawElements(GL_TRIANGLES,
//   count, GL_UNSIGNED_INT, nullptr);
// }

// void SFMLRendererAPI::DrawLines(const Ref<VertexArray>& vertexArray, uint32_t
// vertexCount)
// {
//   vertexArray->Bind();
//   glDrawArrays(GL_LINES, 0, vertexCount);
// }

void SFMLRendererAPI::SetLineWidth(float width) {}
