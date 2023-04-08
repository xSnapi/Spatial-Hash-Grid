#include "Spatial Hash Grid.hpp"

#include "Global Variables.hpp"

#include "Renderer.hpp"

#include "SFML/Graphics/RectangleShape.hpp"

void SpatialHashGrid::Create(sf::Vector2u cellSize, sf::Vector2u size) {
	m_cellSize  = cellSize;
	m_gridSize  = size;
	m_cellCount = size.cwiseDiv(cellSize);

	for (uint32_t y = 0; y < m_cellCount.y; y++)
		for (uint32_t x = 0; x < m_cellCount.x; x++)
			m_Cells[sf::Vector2i(x, y)];
}

void SpatialHashGrid::AppendEntity(Entity& e) {
	int XMin = (e.Position.x + m_gridSize.x / 2.0f - BOUNDS_POSITION.x) / m_cellSize.x;
	int YMin = (e.Position.y + m_gridSize.y / 2.0f - BOUNDS_POSITION.y) / m_cellSize.y;

	int XMax = (e.Position.x + e.Size.x + m_gridSize.x / 2.0f - BOUNDS_POSITION.x) / m_cellSize.x;
	int YMax = (e.Position.y + e.Size.y + m_gridSize.y / 2.0f - BOUNDS_POSITION.y) / m_cellSize.y;

	std::unordered_set<sf::Vector2i> coords;

	coords.insert(sf::Vector2i(XMin, YMin));
	coords.insert(sf::Vector2i(XMax, YMin));
	coords.insert(sf::Vector2i(XMin, YMax));
	coords.insert(sf::Vector2i(XMax, YMax));

	e.m_spatialHashGrid = this;

	for (auto& c : coords) {
		if (m_Cells.find(c) == m_Cells.end())
			return;

		auto& cell = m_Cells[c];

		cell.Entities.insert(&e);

		e.Cells.push_back(&cell);
	}
}

void SpatialHashGrid::DebugRender() {
	for (auto& [coords, c] : m_Cells) {
		sf::RectangleShape rs((sf::Vector2f)m_cellSize - sf::Vector2f(1.0f, 1.0f));
		rs.setPosition((sf::Vector2f)coords.cwiseMul((sf::Vector2i)m_cellSize) - BOUNDS_POSITION * 3.0f);

		if (c.Entities.empty())
			rs.setFillColor(sf::Color(255, 255, 255, 50));
		else
			rs.setFillColor(sf::Color(255, 0, 0, 50));

		Renderer.Draw(rs);
	}
}

void Entity::Update() {
	for (auto& c : Cells)
		c->Entities.erase(this);

	Cells.clear();

	m_spatialHashGrid->AppendEntity(*this);
}

void Entity::AddToGrid(SpatialHashGrid& grid) {
	grid.AppendEntity(*this);
}
