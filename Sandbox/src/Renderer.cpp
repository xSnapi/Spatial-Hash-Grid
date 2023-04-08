#include "Renderer.hpp"

using namespace priv;

void Renderer::Init(sf::RenderWindow& window) {
	m_window = &window;
}

void Renderer::Draw(const sf::Drawable& drawable, const sf::RenderStates& states) {
	m_window->draw(drawable, states);
}

sf::RenderWindow& Renderer::GetWindow() {
	return *m_window;
}
