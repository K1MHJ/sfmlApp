#pragma once

#include <vector>
#include <SFML/Graphics.hpp>

class Renderer2D {
public:
  static void Init(sf::RenderWindow* window);
  static void Shutdown();
  static void BeginScene();
  static void EndScene();
  // Primitives
  static void DrawCircle();
private:
};
