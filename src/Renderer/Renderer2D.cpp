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
void Renderer2D::BeginScene() {
  for(auto& it : s_Data.shapes){
    delete it;    
  }
  s_Data.shapes.clear();
}
void Renderer2D::EndScene() {
  for(auto it = s_Data.shapes.begin();it!=s_Data.shapes.end();it++){
    s_window->draw(**it);
  }
}
void Renderer2D::DrawCircle(float radius, float x, float y, const Color& clr) {
  sf::CircleShape *shape = new sf::CircleShape(radius);
  shape->setPosition(x, y);
  shape->setFillColor(sf::Color(clr.red, clr.green, clr.blue));
  s_Data.shapes.push_back(shape);
}
