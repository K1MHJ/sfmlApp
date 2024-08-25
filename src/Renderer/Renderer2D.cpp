#include "Renderer2D.h"
#include "RenderCommand.h"
#include "SFML/Graphics/RectangleShape.hpp"
#include "SfmlPF.h"
#include "pch.h"
#include <SFML/Graphics.hpp>
struct Renderer2DData {
  std::vector<sf::Shape *> shapes;
  std::vector<sf::Text *> texts;
};
static Renderer2DData s_Data;
static sf::RenderWindow *s_window;
static sf::Font s_font;

static uint8_t s_bkgRed;
static uint8_t s_bkgGreen;
static uint8_t s_bkgBlue;

void Renderer2D::Init(sf::RenderWindow *window) {
  s_window = window;
  if (!s_font.loadFromFile("../assets/fonts/opensans/OpenSans-Regular.ttf")) {
    assert(false);
  }
}
void Renderer2D::Shutdown() {
  for (auto &it : s_Data.shapes) {
    delete it;
    it = nullptr;
  }
  s_Data.shapes.clear();
}
void Renderer2D::BeginScene() {
  for (auto &it : s_Data.shapes) {
    delete it;
    it = nullptr;
  }
  for (auto &it : s_Data.texts) {
    delete it;
    it = nullptr;
  }
  s_Data.shapes.clear();
  s_Data.texts.clear();
}
void Renderer2D::EndScene() {
  for (auto it = s_Data.shapes.begin(); it != s_Data.shapes.end(); it++) {
    s_window->draw(**it);
  }
  for (auto it = s_Data.texts.begin(); it != s_Data.texts.end(); it++) {
    s_window->draw(**it);
  }
  s_window->display();
}
void Renderer2D::Clear(uint8_t red, uint8_t green, uint8_t blue) {
  s_window->clear(sf::Color{red, green, blue, 255});
}
void Renderer2D::DrawCircle(float radius, float x, float y, const Color &clr) {
  sf::CircleShape *shape = new sf::CircleShape(radius);
  shape->setPosition(x, y);
  shape->setFillColor(sf::Color(clr.red, clr.green, clr.blue));
  s_Data.shapes.push_back(shape);
}
void Renderer2D::DrawLineRectangle(float x, float y, float cx, float cy,
                                   const Color &clr, float thickness) {
  sf::RectangleShape *shape = new sf::RectangleShape(sf::Vector2f(cx, cy));
  shape->setPosition(x, y);
  shape->setOutlineThickness(thickness);
  RenderCommand::GetClearColor(s_bkgRed, s_bkgGreen, s_bkgBlue);
  shape->setFillColor(sf::Color(s_bkgRed, s_bkgGreen, s_bkgBlue));
  shape->setOutlineColor(sf::Color(clr.red, clr.green, clr.blue));
  s_Data.shapes.push_back(shape);
}
void Renderer2D::DrawFillRectangle(float x, float y, float cx, float cy,
                                   const Color &clr) {
  sf::RectangleShape *shape = new sf::RectangleShape(sf::Vector2f(cx, cy));
  shape->setPosition(x, y);
  shape->setFillColor(sf::Color(clr.red, clr.green, clr.blue));
  s_Data.shapes.push_back(shape);
}
void Renderer2D::DrawText(const char *str, float x, float y, int textSize, const sf::Color& color) {
  sf::Text *text = new sf::Text();
  text->setPosition(x, y);
  text->setFont(s_font);
  text->setString(str);
  text->setCharacterSize(textSize);
  text->setFillColor(color);
  text->setStyle(sf::Text::Bold);
  s_Data.texts.push_back(text);
}
