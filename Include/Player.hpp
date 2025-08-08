#pragma once
#include <SFML/Graphics.hpp>

class Player
{
  public:
    Player();
    void draw(sf::RenderWindow&);
    void move();
    const sf::ConvexShape& getShape() const;
    sf::ConvexShape& getShape();
    void Bounds(const sf::RenderWindow& window);
    bool Collisions(const sf::RectangleShape& obstacle) const;
    void ResolveCollision(const sf::RectangleShape& wall);
    bool EndPlay(int score);
  private:
    sf::ConvexShape shape;

};
