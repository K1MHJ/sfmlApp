#pragma once

#include <vector>
#include <SFML/Graphics.hpp>

struct Color{
  uint8_t red, green, blue;
};

class Renderer2D {
public:
  static void Init(sf::RenderWindow* window);
  static void Shutdown();
  static void BeginScene();
  static void EndScene();
  // Primitives
  static void DrawCircle(float radius, float x, float y, const Color& clr);
private:
};
