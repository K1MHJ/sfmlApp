#include "Renderer2D.h"
#include "SfmlPF.h"
#include <SFML/Graphics.hpp>

struct Renderer2DData {
  std::vector<sf::Shape *> shapes;
};
static Renderer2DData s_Data;
static sf::RenderWindow* s_window;

void Renderer2D::Init(sf::RenderWindow *window) { s_window = window; }
void Renderer2D::Shutdown() {}
void Renderer2D::BeginScene() {}
void Renderer2D::EndScene() {
  for(auto it = s_Data.shapes.begin();it!=s_Data.shapes.end();it++){
    s_window->draw(**it);
  }
}
void Renderer2D::DrawCircle() {
  sf::CircleShape *shape = new sf::CircleShape(50);
  shape->setPosition(0, 0);
  shape->setFillColor(sf::Color(100, 250, 50));
  s_Data.shapes.push_back(shape);
}
