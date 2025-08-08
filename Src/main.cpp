#include <SFML/Graphics.hpp>
#include "Player.hpp"
#include "Star.hpp"
#include "Cutscene.hpp"
#include <iostream>

int main() {
  int score = 0;
  bool inCutscene = false;

  Cutscene cutscene;

  sf::Clock clock;
    sf::RenderWindow window(sf::VideoMode(800, 600), "Triangle Player");
    Player player;
    sf::RectangleShape lowVisibility;
    lowVisibility.setSize(sf::Vector2f(800.f, 800.f));
    lowVisibility.setFillColor(sf::Color(0, 0, 0, 200));
    
    sf::RectangleShape wall;
    wall.setSize(sf::Vector2f(500.f, 50.f));
    wall.setPosition(sf::Vector2f(450.f, 300.f));
    wall.setFillColor(sf::Color::Red);

    sf::RectangleShape wall1;
    wall1.setSize(sf::Vector2f(500.f, 50.f));
    wall1.setPosition(sf::Vector2f(0.f, 450));

    sf::CircleShape light(100.f);
    light.setFillColor(sf::Color(0, 0, 0, 0));
    light.setOutlineColor(sf::Color::Black);
    light.setOutlineThickness(50.f);

    std::vector<Star> stars = {
      Star(sf::Vector2f(100.f, 150.f)),
      Star(sf::Vector2f(300.f, 200.f)),
      Star(sf::Vector2f(500.f, 100.f))
};


  while (window.isOpen()) {
    sf::Event event;
    while (window.pollEvent(event)) {
        if (event.type == sf::Event::Closed)
          window.close();
    }
  if (inCutscene == false)
  {
    player.draw(window);
    player.move();
    player.Bounds(window);
    if (player.Collisions(wall))
    {
      player.ResolveCollision(wall);
      std::cout << "You hit a danger!" << std::endl;
      window.close();
    }
    if (player.Collisions(wall1))
    {
      player.ResolveCollision(wall1);
    }
  }
  
      for (auto& star : stars) {
        if (star.checkCollision(player.getShape())) {
            star.collect();
            score += 1;
        }
    }

    window.clear();
    // Draw stars first
    for (auto& star : stars)
        star.draw(window);

   
    float dt = clock.restart().asSeconds();

    if (player.EndPlay(score) == false)
    {
      if (!inCutscene)
      {
        cutscene.start();
        inCutscene = true;
        light.setOutlineColor(sf::Color::Transparent);
        lowVisibility.setFillColor(sf::Color(0, 0, 0, 50));
      }
      window.clear();
      
      if (inCutscene) {
            cutscene.update(dt);
            cutscene.draw(window);
            

            if (cutscene.isFinished()) {
                // Cutscene is done — transition to next state
                // You could reset the game, show credits, etc.
                inCutscene = false;
                score = 0; // Example reset
                window.close();
            }
        } else {
            // 🕹️ Regular gameplay logic here
            // Example: draw player, stars, handle input

            // For demo purposes, simulate star collection
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && score < 3) {
                score++;
                sf::sleep(sf::seconds(0.2f)); // prevent rapid increment
            }

        }


    }
    light.setPosition(player.getShape().getPosition() - sf::Vector2f(100.f, 100.f));
  
    window.draw(lowVisibility);

    window.draw(light);
    if (inCutscene == false)
    {
      window.draw(wall1);
      window.draw(wall);
      player.draw(window);
    }
    else 
    {
      player.getShape().setPosition(50.f, 510.f);  
      player.getShape().setRotation(90.f);
    std::cout << "Player places the stars -- shadow, nature, and light -- on the protective shrine," << std::endl << "revealing the Scepter which protects the earth, and the Villain trying to harm earth." << std::endl;
      player.draw(window);
    }
    window.display();

    
}
    return 0;
}
