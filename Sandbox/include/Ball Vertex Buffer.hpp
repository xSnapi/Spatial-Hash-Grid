#pragma once

#include "Ball.hpp"

#include "SFML/Graphics/VertexBuffer.hpp"
#include "SFML/Graphics/Shader.hpp"

class BallVertexBuffer {
public:
	BallVertexBuffer();
	~BallVertexBuffer() = default;

	void Clear();

	void Render(const Ball& ball);

	void Flush();

private:
	sf::VertexBuffer m_buffer;
	sf::Shader		 m_shader;

	uint32_t		 m_currentBall = 0;

	sf::Vector2f m_texCoords[6];
};
