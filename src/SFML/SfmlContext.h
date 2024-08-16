#pragma once

#include "GraphicsContext.h"
#include <SFML/Graphics.hpp>

class SFMLContext: public GraphicsContext
{
public:
  SFMLContext(sf::RenderWindow* windowHandle);

  virtual void Init() override;
  virtual void SwapBuffers() override;

private:
  sf::RenderWindow* m_WindowHandle;
};
