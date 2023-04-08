#pragma once

#include "SFML/Graphics/Drawable.hpp"
#include "SFML/Graphics/Vertex.hpp"

class BordersVisual : public sf::Drawable {
public:
	BordersVisual();
	~BordersVisual() = default;

private:
	sf::Vertex m_lines[5]; // actuall line strips

	void CreateLines();

	virtual void draw(sf::RenderTarget& target, const sf::RenderStates& states) const override;
};
