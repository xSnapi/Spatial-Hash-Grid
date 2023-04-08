#include "Borders Visual.hpp"

#include "Global Variables.hpp"

#include "SFML/Graphics.hpp"

BordersVisual::BordersVisual() {
	CreateLines();
}

void BordersVisual::CreateLines(){
	m_lines[0] = sf::Vector2f(-BOUNDS_SIZE.x + BOUNDS_POSITION.x, -BOUNDS_SIZE.y + BOUNDS_POSITION.y);
	m_lines[1] = sf::Vector2f(-BOUNDS_SIZE.x + BOUNDS_POSITION.x,  BOUNDS_SIZE.y + BOUNDS_POSITION.y);
	m_lines[2] = sf::Vector2f( BOUNDS_SIZE.x + BOUNDS_POSITION.x,  BOUNDS_SIZE.y + BOUNDS_POSITION.y);
	m_lines[3] = sf::Vector2f( BOUNDS_SIZE.x + BOUNDS_POSITION.x, -BOUNDS_SIZE.y + BOUNDS_POSITION.y);
	m_lines[4] = sf::Vector2f(-BOUNDS_SIZE.x + BOUNDS_POSITION.x, -BOUNDS_SIZE.y + BOUNDS_POSITION.y);
}

void BordersVisual::draw(sf::RenderTarget& target, const sf::RenderStates& states) const {
	target.draw(m_lines, 5, sf::LineStrip);
}
