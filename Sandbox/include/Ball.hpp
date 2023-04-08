#pragma once

#include "SFML/Graphics/Drawable.hpp"
#include "SFML/Graphics/Color.hpp"
#include "SFML/System/Vector2.hpp"

#include "Time Steps.hpp"

#include "Global Variables.hpp"

#include "Spatial Hash Grid.hpp"

//#include "Simulation.hpp"

struct Ball {
	Ball(float radius, sf::Vector2f position, float speed, sf::Vector2f direction, sf::Color color = sf::Color::White);
	~Ball() = default;

	void Update() {
		Position += Direction * Speed * dt;

		KeepInBounds();

		Entity.Position = Position - sf::Vector2f(Radius, Radius);
		Entity.Update();
	}

	void KeepInBounds() {
		bool left	= Position.x - Radius <= -BOUNDS_SIZE.x + BOUNDS_POSITION.x;
		bool right	= Position.x + Radius >=  BOUNDS_SIZE.x + BOUNDS_POSITION.x;
		bool top	= Position.y - Radius <= -BOUNDS_SIZE.y + BOUNDS_POSITION.y;
		bool bottom = Position.y + Radius >=  BOUNDS_SIZE.y + BOUNDS_POSITION.y;

		if (left || right) {
			Direction.x = -Direction.x;

			Position.x = left ? -BOUNDS_SIZE.x + BOUNDS_POSITION.x + Radius : BOUNDS_SIZE.x + BOUNDS_POSITION.x - Radius;
		}

		if (top || bottom) {
			Direction.y = -Direction.y;

			Position.y = top ? -BOUNDS_SIZE.y + BOUNDS_POSITION.y + Radius : BOUNDS_SIZE.y + BOUNDS_POSITION.y - Radius;
		}
	}

	void Bounce(Ball& other, sf::Vector2f MTV) {
		MTV /= 2.0f;

		Position += MTV;

		other.Position += -MTV;

		Direction = (MTV.normalized() + Direction).normalized();

		other.Direction = (- MTV.normalized() + other.Direction).normalized();
	}

	sf::Vector2f Direction;
	sf::Vector2f Position;
	sf::Color	 Color;
	float		 Radius;
	float		 Speed;

	Entity		 Entity;
};
