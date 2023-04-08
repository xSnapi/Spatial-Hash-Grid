#pragma once

#include "SFML/Graphics/View.hpp"

class Camera {
public:
	Camera(sf::Vector2f center, sf::Vector2f size);

	Camera()  = default;
	~Camera() = default;

	void Create(sf::Vector2f center, sf::Vector2f size);

	void SetScale(float zoom);
	void OffsetScale(float offset);

	void SetRotation(sf::Angle angle);

	void Move(sf::Vector2f offset);
	void SetCenter(sf::Vector2f center);
	void Rotate(sf::Angle angle);

	sf::Vector2f GetCenter() const;
	float GetScale() const;
	sf::Angle GetRotation() const;
	sf::Vector2f GetSize() const;

	bool IsCreated() const;

	const sf::View& GetView() const;

private:
	sf::View m_view;

	float m_scale = 1.0f;

	bool  m_created = false;;
};
