#include "pch.h"
#include "SfmlContext.h"

SFMLContext::SFMLContext(sf::RenderWindow *windowHandle)
    : m_WindowHandle(windowHandle) {
  CORE_ASSERT(windowHandle, "Window handle is null");
}

void SFMLContext::Init() {
  PROFILE_FUNCTION();
  CORE_INFO("SFML Info:");
}

void SFMLContext::SwapBuffers() { 
  PROFILE_FUNCTION();
  m_WindowHandle->display();
}
