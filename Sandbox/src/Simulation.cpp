#include "Simulation.hpp"
#include "Time Steps.hpp"

#include "Renderer.hpp"

#include "Global Variables.hpp"
#include "Random.hpp"

#include "Collision.hpp"

#include "Application.hpp"

#include "Global Variables.hpp"

#include "SFML/Graphics/RectangleShape.hpp"
#include "SFML/Window/Keyboard.hpp"

// Note! run in release mode

Simulation::Simulation() {
	CreateSpatialGrid();

	CreateBalls();
	CreateText();
}

void Simulation::Update() {
	UpdateBalls();
	UpdateText();

	CheckForKeyPress();
}

void Simulation::Render() {
	m_ballVertexBuffer.Clear();

	for (auto& b : m_Balls)
		m_ballVertexBuffer.Render(b);

	m_ballVertexBuffer.Flush();

	Renderer.Draw(m_bordersVisual);

	if(m_debugDraw)
		SpatialGrid.DebugRender();

	auto& window = Renderer.GetWindow();
	
	window.setView(window.getDefaultView());
	
	sf::RectangleShape rs(sf::Vector2f(580.0f, 80.0f));
	rs.setFillColor(sf::Color(84, 55, 138, 120));
	rs.setPosition(sf::Vector2f(0.0f, WINDOW_SIZE.y - 80.0f));

	Renderer.Draw(rs);
	Renderer.Draw(m_fpsCounter);
	Renderer.Draw(m_gridInfo);
	Renderer.Draw(m_drawInfo);

	window.setView(MainCamera.GetView());
}

void Simulation::CheckForKeyPress() {
	static bool spacePressed = false;
	static bool fPressed = false;

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && !spacePressed) {
		m_enabled = !m_enabled;
		spacePressed = true;
	}

	if (!sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
		spacePressed = false;

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::F) && !fPressed) {
		m_debugDraw = !m_debugDraw;
		fPressed = true;
	}

	if (!sf::Keyboard::isKeyPressed(sf::Keyboard::F))
		fPressed = false;
}

void Simulation::CreateSpatialGrid() {
	SpatialGrid.Create(sf::Vector2u(50, 50), (sf::Vector2u)BOUNDS_SIZE * 2u);
}

void Simulation::UpdateText() {
	m_fpsCounter.setString("FPS - " + std::to_string((int)(1.0f / dt)));

	// yeah i know
	m_gridInfo.setString(m_enabled ? "\"SPACE\" Spatial Hash Grid - Enabled" : "\"SPACE\" Spatial Hash Grid - Disabled");
	m_drawInfo.setString(m_debugDraw ? "\"F\" Grid Drawing - Enabled" : "\"F\" Grid Drawing - Disabled");
}

void Simulation::CreateText() {
	m_font.loadFromFile("res/font.ttf");

	{
		m_fpsCounter.setFont(m_font);
		m_fpsCounter.setPosition(sf::Vector2f(10.0f, 10.0f));
		m_fpsCounter.setOutlineThickness(1.0f);
	}

	// yeah i know
	{
		m_gridInfo.setFont(m_font);

		m_gridInfo.setCharacterSize(20);
		m_gridInfo.setString("Spatial Hash Grid - Disabled");
		m_gridInfo.setPosition(sf::Vector2f(10.0f, WINDOW_SIZE.y - 60.0f));
		m_gridInfo.setOutlineThickness(1.5f);
	}

	// yep
	{
		m_drawInfo.setFont(m_font);

		m_drawInfo.setCharacterSize(20);
		m_drawInfo.setString("Grid Drawing - Disabled");
		m_drawInfo.setPosition(sf::Vector2f(10.0f, WINDOW_SIZE.y - 30.0f));
		m_drawInfo.setOutlineThickness(1.5f);
	}
}

void Simulation::UpdateBalls() {
	for (auto& b : m_Balls)
		b.Update();

	if(m_enabled)
		CheckBallCollisionWithSpatialHasGrid();
	else
		CheckBallCollision();
}

void Simulation::CreateBalls() {
	m_Balls.reserve(MAX_BALLS * 2); // very fucking necessary

	for (uint32_t i = 0; i < MAX_BALLS; i++) {
		float radius = 25.0f;

		float speed = Random::Rand(50.0f, 250.0f);

		float dirX  = Random::Rand(-1.0f, 1.0f);
		float dirY  = Random::Rand(-1.0f, 1.0f);

		float posX  = Random::Rand(-BOUNDS_SIZE.x + BOUNDS_POSITION.x + radius, BOUNDS_SIZE.x + BOUNDS_POSITION.x - radius);
		float posY  = Random::Rand(-BOUNDS_SIZE.y + BOUNDS_POSITION.y + radius, BOUNDS_SIZE.y + BOUNDS_POSITION.y - radius);

		sf::Color color(Random::Rand(50, 255), Random::Rand(50, 255), Random::Rand(50, 255), 255);

		m_Balls.emplace_back
		(
			radius,
			sf::Vector2f(posX, posY),
			speed,
			sf::Vector2f(dirX, dirY),
			color
		);
	}
}

void Simulation::CheckBallCollision() {
	for (uint32_t i = 0; i < m_Balls.size(); i++) {
		for (uint32_t j = 0; j < m_Balls.size(); j++) {
			if (j == i)
				continue;

			sf::Vector2f MTV;
			bool good = Collision::CircleCollision(m_Balls[i], m_Balls[j], &MTV);

			if(good)
				m_Balls[i].Bounce(m_Balls[j], MTV);
		}
	}
}

void Simulation::CheckBallCollisionWithSpatialHasGrid() {
	for (auto& b : m_Balls) {
		for (auto& cell : b.Entity.Cells) {
			for (auto& e : cell->Entities) {

				Ball* other = (Ball*)e->Object;

				if (other == &b)
					continue;

				sf::Vector2f MTV;
				bool good = Collision::CircleCollision(b, *other, &MTV);

				if (good)
					b.Bounce(*other, MTV);
			}

		}
	}
}
