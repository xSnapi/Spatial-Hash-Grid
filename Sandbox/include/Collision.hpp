#pragma once

#include "Ball.hpp"

class Collision {
public:
	Collision()  = default;
	~Collision() = default;

	static bool CircleCollision(const Ball& body, const Ball& other, sf::Vector2f* MTV = nullptr);

};
