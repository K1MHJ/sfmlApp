#pragma once

#include <Color.h>
#include <SFML/Graphics.hpp>
#include <vector>

class Renderer2D {
public:
  static void Init(sf::RenderWindow *window);
  static void Shutdown();
  static void BeginScene();
  static void EndScene();
  // Primitives
  static void Clear(uint8_t red, uint8_t green, uint8_t blue);
  static void DrawCircle(float radius, float x, float y, const Color &clr);
  static void DrawLineRectangle(float x, float y, float cx, float cy,
                                const Color &clr, float thickness = 1.0f);
  static void DrawFillRectangle(float x, float y, float cx, float cy,
                                const Color &clr);
  static void DrawText(const char* text, float x, float y, int textSize, const sf::Color& color);
private:
};
