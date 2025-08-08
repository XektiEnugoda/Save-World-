#include "Cutscene.hpp"
#include <iostream>
#include <cmath>


    // 🌟 Stars
  sf::ConvexShape createStar(float radiusOuter, float radiusInner) {
    sf::ConvexShape star;
    star.setPointCount(10); // 5 outer + 5 inner

    float angleStep = 360.f / 10;

    for (int i = 0; i < 10; ++i) {
        float angleDeg = i * angleStep - 90.f;
        float angleRad = angleDeg * 3.14159265f / 180.f;
        float radius = (i % 2 == 0) ? radiusOuter : radiusInner;

        star.setPoint(i, sf::Vector2f(
            std::cos(angleRad) * radius,
            std::sin(angleRad) * radius
        ));
    }

    return star;
  }

Cutscene::Cutscene() : currentPhase(Phase::EmptyMountain), finished(false) {
    // 🗻 Mountain triangles
    sf::ConvexShape triangle1;
    triangle1.setPointCount(3);
    triangle1.setPoint(0, sf::Vector2f(100, 500));
    triangle1.setPoint(1, sf::Vector2f(200, 300));
    triangle1.setPoint(2, sf::Vector2f(300, 500));
    triangle1.setFillColor(sf::Color(100, 100, 100));
    mountainShapes.push_back(triangle1);

    sf::ConvexShape triangle2;
    triangle2.setPointCount(3);
    triangle2.setPoint(0, sf::Vector2f(250, 500));
    triangle2.setPoint(1, sf::Vector2f(350, 320));
    triangle2.setPoint(2, sf::Vector2f(450, 500));
    triangle2.setFillColor(sf::Color(120, 120, 120));
    mountainShapes.push_back(triangle2);

    // 🌟 Stars
    starLeft = createStar(20.f, 10.f);
    starMiddle = createStar(20.f, 10.f);
    starRight = createStar(20.f, 10.f);


    starLeft.setFillColor(sf::Color::Yellow);
    starMiddle.setFillColor(sf::Color::Yellow);
    starRight.setFillColor(sf::Color::Yellow);

    starLeft.setPosition(180, 400);
    starMiddle.setPosition(220, 400);
    starRight.setPosition(320, 400);

    // 🔮 Scepter
    scepterShaft.setSize(sf::Vector2f(10, 100));
    scepterShaft.setFillColor(sf::Color(160, 35, 240, 200));
    scepterShaft.setPosition(225, 300);

    scepterGem.setRadius(15);
    scepterGem.setFillColor(sf::Color::Transparent);
    scepterGem.setPosition(390, 285);

    // 😈 Villain
    villainHead.setRadius(30);
    villainHead.setFillColor(sf::Color::Red);
    villainHead.setPosition(600, 300);

    villainBody.setSize(sf::Vector2f(40, 80));
    villainBody.setFillColor(sf::Color::Red);
    villainBody.setPosition(610, 330);

    villainEyeLeft.setRadius(5);
    villainEyeRight.setRadius(5);
    villainEyeLeft.setFillColor(sf::Color::White);
    villainEyeRight.setFillColor(sf::Color::White);
    villainEyeLeft.setPosition(615, 310);
    villainEyeRight.setPosition(630, 310);
}
void Cutscene::start() {
    currentPhase = Phase::EmptyMountain;
    timer.restart();
    finished = false;
}

void Cutscene::update(float dt) {
    sf::Time elapsed = timer.getElapsedTime();

    switch (currentPhase) {
        case Phase::EmptyMountain:
            if (elapsed.asSeconds() > 1.0f) {
                currentPhase = Phase::StarsInserted;
                timer.restart();
            }
            break;

        case Phase::StarsInserted:
            if (elapsed.asSeconds() > 2.0f) {
                currentPhase = Phase::Crumble;
                timer.restart();
            }
            break;

        case Phase::Crumble:
            // Optional: animate triangles falling
            for (auto& tri : mountainShapes)
            {
                tri.move(0.f, 1.f); // crude crumble effect
                starLeft.move(0.f, 1.f);
                starMiddle.move(0.f, 1.f);
                starRight.move(0.f, 1.f);
                
               
            }
               
            if (elapsed.asSeconds() > 2.0f) {
                currentPhase = Phase::ScepterReveal;
                timer.restart();
                
                starLeft.setPosition(200, 300);
                starMiddle.setPosition(220, 300);
                starRight.setPosition(250, 300);


            }
            break;

        case Phase::ScepterReveal:
            if (elapsed.asSeconds() > 2.0f) {
                currentPhase = Phase::Vanquish;
                timer.restart();

                           }
            break;

        case Phase::Vanquish:
            // Optional: fade villain or animate blast
            if (elapsed.asSeconds() > 2.0f) {
                finished = true;
            }
            break;
    }
}

void Cutscene::draw(sf::RenderWindow& window) {
    if (currentPhase <= Phase::Crumble) {
        for (const auto& tri : mountainShapes)
            window.draw(tri);
    }

    if (currentPhase >= Phase::StarsInserted) {
        window.draw(starLeft);
        window.draw(starMiddle);
        window.draw(starRight);
    }

    if (currentPhase >= Phase::ScepterReveal) {
        window.draw(scepterShaft);
        window.draw(scepterGem);
    }

    if (currentPhase >= Phase::Vanquish) {
        window.draw(villainHead);
        window.draw(villainBody);
        window.draw(villainEyeLeft);
        window.draw(villainEyeRight);
    }
}

bool Cutscene::isFinished() const {
    return finished;
}
