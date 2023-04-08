#include "Ball Vertex Buffer.hpp"

#include "Global Variables.hpp"

#include "Renderer.hpp"

BallVertexBuffer::BallVertexBuffer() {
	uint32_t vertices = 6 * MAX_BALLS;

	m_buffer.create(vertices);
	m_buffer.setPrimitiveType(sf::Triangles);
	m_buffer.setUsage(sf::VertexBuffer::Static);

	m_shader.loadFromFile("res/circle.vert", "res/circle.frag");

	m_texCoords[0] = sf::Vector2f(0.0f, 0.0f);
	m_texCoords[1] = sf::Vector2f(1.0f, 0.0f);
	m_texCoords[2] = sf::Vector2f(1.0f, 1.0f);
	m_texCoords[3] = sf::Vector2f(0.0f, 0.0f);
	m_texCoords[4] = sf::Vector2f(1.0f, 0.0f);
	m_texCoords[5] = sf::Vector2f(1.0f, 1.0f);
}

void BallVertexBuffer::Clear() {
	m_currentBall = 0;

	m_buffer.update(0, 6 * MAX_BALLS, 0);
}

void BallVertexBuffer::Render(const Ball& ball) {
	sf::Vector2f halfSize(ball.Radius, ball.Radius);

	sf::Vertex verts[6] =
	{
		sf::Vector2f(-halfSize.x, -halfSize.y),
		sf::Vector2f( halfSize.x, -halfSize.y),
		sf::Vector2f( halfSize.x,  halfSize.y),
		sf::Vector2f(-halfSize.x, -halfSize.y),
		sf::Vector2f(-halfSize.x,  halfSize.y),
		sf::Vector2f( halfSize.x,  halfSize.y),
	};

	for (uint32_t i = 0; i < 6; i++) {
		verts[i].position += ball.Position;
		verts[i].texCoords = m_texCoords[i];

		verts[i].color = ball.Color;
	}

	m_buffer.update(verts, 6, m_currentBall * 6);

	m_currentBall++;
}

void BallVertexBuffer::Flush() {
	Renderer.Draw(m_buffer, &m_shader);
}
