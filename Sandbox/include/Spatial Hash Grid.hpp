#pragma once

#include <unordered_map>
#include <unordered_set>
#include <vector>

#include "SFML/System/Vector2.hpp"

struct Cell;
class SpatialHashGrid;

struct Entity {
	void* Object = nullptr;

	sf::Vector2f Position;
	sf::Vector2f Size;

	void Update();
	void AddToGrid(SpatialHashGrid& grid);

	std::vector<Cell*> Cells;

private:
	SpatialHashGrid* m_spatialHashGrid = nullptr;

	friend class SpatialHashGrid;
};

struct Cell {
	std::unordered_set<Entity*> Entities;
};

namespace std {
	template<> struct hash<sf::Vector2i> {
		std::size_t operator()(const sf::Vector2i& p) const noexcept {
			return (size_t)(p.x + p.y);
		}
	};
}

class SpatialHashGrid {
public:
	SpatialHashGrid()  = default;
	~SpatialHashGrid() = default;

	void Create(sf::Vector2u cellSize, sf::Vector2u size);

	void AppendEntity(Entity& e);

	void DebugRender();

private:
	sf::Vector2u m_cellSize;
	sf::Vector2u m_cellCount;
	sf::Vector2u m_gridSize;

	std::unordered_map<sf::Vector2i, Cell> m_Cells;
};
