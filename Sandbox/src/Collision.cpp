#include "Collision.hpp"

bool Collision::CircleCollision(const Ball& body, const Ball& other, sf::Vector2f* MTV) {
    sf::Vector2f diff(body.Position - other.Position);

    float length = diff.length();
    float sum    = body.Radius + other.Radius;

    if (length >= sum)
        return false;

    sum -= length;

    diff = diff.normalized();

    if(MTV)
        *MTV = diff * sum;

    return true;
}
