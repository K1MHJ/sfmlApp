#include "pch.h"
#include "GraphicsContext.h"
#include "Renderer.h"
#include "SfmlContext.h"

Scope<GraphicsContext> GraphicsContext::Create(void* window)
{
  switch(Renderer::GetAPI())
  {
    case RendererAPI::API::None: return nullptr;
    case RendererAPI::API::SFML: return CreateScope<SFMLContext>(static_cast<sf::RenderWindow*>(window));
  }
}



