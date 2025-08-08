#pragma once
#include <SFML/Graphics.hpp>

class Star
{
  public:
    Star(sf::Vector2f position); // Constructor with position
    void draw(sf::RenderWindow& window) const;
    bool checkCollision(const sf::ConvexShape& player) const;
    bool isCollected() const;
    void collect();

  private:
    sf::ConvexShape shape;
    bool collected;

};
