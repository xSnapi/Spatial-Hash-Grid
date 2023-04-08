#pragma once

#include "SFML/Graphics/RenderWindow.hpp"

namespace priv {
	class Renderer {
	public:
		void Init(sf::RenderWindow& window);

		void Draw(const sf::Drawable& drawable, const sf::RenderStates& states = sf::RenderStates::Default);

		sf::RenderWindow& GetWindow();

	private:
		sf::RenderWindow* m_window = nullptr;
	};
}

inline priv::Renderer Renderer;
