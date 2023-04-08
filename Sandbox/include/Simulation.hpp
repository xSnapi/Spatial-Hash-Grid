#pragma once

#include <vector>

#include "Ball Vertex Buffer.hpp"
#include "Borders Visual.hpp"
#include "Ball.hpp"

#include "Spatial Hash Grid.hpp"

#include "SFML/Graphics/Text.hpp"
#include "SFML/Graphics/Font.hpp"

inline SpatialHashGrid SpatialGrid;

class Simulation {
public:
	Simulation();
	~Simulation() = default;

	void Update();
	void Render();

private:
	std::vector<Ball> m_Balls;

	BallVertexBuffer m_ballVertexBuffer;

	sf::Font m_font;

	sf::Text m_fpsCounter;
	sf::Text m_gridInfo;
	sf::Text m_drawInfo;

	BordersVisual m_bordersVisual;

	bool m_enabled = false;
	bool m_debugDraw = false;

	void CheckForKeyPress();

	void CreateSpatialGrid();

	void UpdateText();
	void CreateText();

	void UpdateBalls();
	void CreateBalls();

	void CheckBallCollision();
	void CheckBallCollisionWithSpatialHasGrid();
};
