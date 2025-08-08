#pragma once
#include <SFML/Graphics.hpp>
#include <vector>

class Cutscene {
public:
    Cutscene();
    void start();
    void update(float dt);
    void draw(sf::RenderWindow& window);
    bool isFinished() const;
    
private:
    enum class Phase {
        EmptyMountain,
        StarsInserted,
        Crumble,
        ScepterReveal,
        Vanquish
    };

    Phase currentPhase;
    sf::Clock timer;
    bool finished;

    // Mountain made of triangles
    std::vector<sf::ConvexShape> mountainShapes;

    // Stars
   sf::ConvexShape starLeft, starMiddle, starRight;
    // Scepter
    sf::RectangleShape scepterShaft;
    sf::CircleShape scepterGem;

    // Villain
    sf::CircleShape villainHead;
    sf::RectangleShape villainBody;
    sf::CircleShape villainEyeLeft, villainEyeRight;
};
