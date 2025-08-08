#include "Player.hpp"
#include <ctime>
#include <chrono>

Player::Player() 
{
  shape.setPointCount(3);
  shape.setPoint(0, sf::Vector2f(0.f, 50.f));
  shape.setPoint(1, sf::Vector2f(25.f, 0.f));
  shape.setPoint(2, sf::Vector2f(50.f, 50.f));
  shape.setFillColor(sf::Color::Magenta);
  shape.setOrigin(25.f, 25.f);
  shape.setPosition(800.f, 590.f);
}

  void Player::move()
{
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
  {
    shape.move(-1.0f, 0.f);
    shape.setRotation(270.f); // Rotates around the center
  } 
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
  {
     shape.move(1.0f, 0.f);
     shape.setRotation(90.f);
  }
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
  {
     shape.move(0.f, -1.f);
     shape.setRotation(0.f);
  }
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
  {
     shape.move(0.f,1.f);
     shape.setRotation(180.f);
  }
}
void Player::draw(sf::RenderWindow& window) {
    window.draw(shape);
}

const sf::ConvexShape& Player::getShape() const {
    return shape;
}
sf::ConvexShape& Player::getShape()
{
  return shape;
}
void Player::Bounds(const sf::RenderWindow& window)
{
  sf::Vector2f position = shape.getPosition();
  sf::FloatRect bound = shape.getGlobalBounds();
  
  float left = position.x - bound.width / 2;
  float right = position.x + bound.width / 2;
  float top = position.y - bound.height / 2;
  float down = position.y + bound.height / 2;
    
  float wWidth = window.getSize().x;
  float wHeight = window.getSize().y;

  if (left < 0) 
    position.x = bound.width / 2;
  if (right > wWidth) 
    position.x = wWidth - bound.width / 2;
  if (top < 0)
    position.y = bound.height / 2;
  if (down > wHeight)
    position.y = wHeight - bound.height / 2;
  
  shape.setPosition(position);
}

bool Player::Collisions(const sf::RectangleShape& obstacle) const
{
  return (shape.getGlobalBounds().intersects(obstacle.getGlobalBounds()));
}

void Player::ResolveCollision(const sf::RectangleShape& wall) {
    sf::FloatRect playerBounds = shape.getGlobalBounds();
    sf::FloatRect wallBounds = wall.getGlobalBounds();
    sf::FloatRect intersection;

    if (playerBounds.intersects(wallBounds, intersection)) {
        // Determine the smallest overlap axis
        float overlapLeft   = intersection.width;
        float overlapTop    = intersection.height;

        // Push out horizontally or vertically based on smaller overlap
        if (overlapLeft < overlapTop) {
            if (playerBounds.left < wallBounds.left)
                shape.move(-overlapLeft, 0); // push left
            else
                shape.move(overlapLeft, 0);  // push right
        } else {
            if (playerBounds.top < wallBounds.top)
                shape.move(0, -overlapTop); // push up
            else  
                shape.move(0, overlapTop);  // push down
        }
    }
}

bool Player::EndPlay(int score)
{
  if (score == 3)
  {
      return false;
  }
  return true;
}
