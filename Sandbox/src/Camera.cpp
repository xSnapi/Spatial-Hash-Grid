#include "Camera.hpp"

Camera::Camera(sf::Vector2f center, sf::Vector2f size) {
	Create(center, size);
}

void Camera::Create(sf::Vector2f center, sf::Vector2f size) {
	m_view.setSize(size);
	m_view.setCenter(center);

	m_created = true;
}

void Camera::SetScale(float zoom) {
	m_view.zoom(1.0f / m_scale);

	m_view.zoom(zoom);

	m_scale = zoom;
}

void Camera::OffsetScale(float offset) {
	m_view.zoom(offset);

	m_scale *= offset;
}

void Camera::SetRotation(sf::Angle angle) {
	m_view.setRotation(angle);
}

void Camera::Move(sf::Vector2f offset) {
	m_view.move(offset);
}

void Camera::SetCenter(sf::Vector2f center) {
	m_view.setCenter(center);
}

void Camera::Rotate(sf::Angle angle) {
	m_view.rotate(angle);
}

sf::Vector2f Camera::GetCenter() const {
	return m_view.getCenter();
}

float Camera::GetScale() const {
	return m_scale;
}

sf::Angle Camera::GetRotation() const {
	return m_view.getRotation();
}

sf::Vector2f Camera::GetSize() const {
	return m_view.getSize();
}

bool Camera::IsCreated() const {
	return m_created;
}

const sf::View& Camera::GetView() const {
	return m_view;
}
