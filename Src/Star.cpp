#include "Star.hpp"
#include <cmath>

Star::Star(sf::Vector2f position) : collected(false) {
    shape.setPointCount(10); // 5 outer + 5 inner points

    float radiusOuter = 20.f;
    float radiusInner = 10.f;
    float angleStep = 360.f / 10;

    for (int i = 0; i < 10; ++i) {
        float angleDeg = i * angleStep - 90.f;
        float angleRad = angleDeg * 3.14159265f / 180.f;
        float radius = (i % 2 == 0) ? radiusOuter : radiusInner;
        shape.setPoint(i, sf::Vector2f(
            std::cos(angleRad) * radius,
            std::sin(angleRad) * radius
        ));
    }

    shape.setFillColor(sf::Color::Yellow);
    shape.setOrigin(radiusOuter, radiusOuter); // Center origin
    shape.setPosition(position);
}

void Star::draw(sf::RenderWindow& window) const {
    if (!collected)
        window.draw(shape);
}

bool Star::checkCollision(const sf::ConvexShape& player) const {
    return !collected && shape.getGlobalBounds().intersects(player.getGlobalBounds());
}

bool Star::isCollected() const {
    return collected;
}

void Star::collect() {
    collected = true;
}
