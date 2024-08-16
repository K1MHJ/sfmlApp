#include "pch.h"
#include "RendererAPI.h"
#include "SfmlRendererAPI.h"

RendererAPI::API RendererAPI::s_API = RendererAPI::API::SFML;

Scope<RendererAPI> RendererAPI::Create()
{
  switch(s_API)
  {
    case RendererAPI::API::None: return nullptr;
    case RendererAPI::API::SFML: return CreateScope<SFMLRendererAPI>();
  }
}
