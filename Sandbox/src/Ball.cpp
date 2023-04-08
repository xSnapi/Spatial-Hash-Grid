#include "Ball.hpp"

#include "Simulation.hpp"

Ball::Ball(float radius, sf::Vector2f position, float speed, sf::Vector2f direction, sf::Color color)
	: Direction(direction)
	, Position(position)
	, Radius(radius)
	, Color(color)
	, Speed(speed)
{
	Entity.Object	= this;

	Entity.Position = Position - sf::Vector2f(Radius, Radius);
	Entity.Size     = sf::Vector2f(Radius, Radius) * 2.0f;

	SpatialGrid.AppendEntity(Entity);
}
