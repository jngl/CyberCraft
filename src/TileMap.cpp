//
// Created by jngl on 27/04/2020.
//

#include "TileMap.h"

TileMap::TileMap(const TileTypeRegistry &tiles) :
		m_types(tiles) {
	for (int x(0); x < sizeX; ++x) {
		for (int y(0); y < sizeY; ++y) {
			set({x, y}, defaultTileName);
		}
	}

	m_background.setFillColor(sf::Color(0, 150, 0));
	m_background.setSize(sf::Vector2f(sizeX*16, sizeY*16));
}

void TileMap::set(sf::Vector2i position, std::string_view typeName) {
	at(position).set(m_types, typeName, position);
}

void TileMap::draw(sf::RenderTarget &renderTarget) {
	renderTarget.draw(m_background);
	for (Tile &tile : m_tiles) {
		tile.draw(renderTarget);
	}
}

Tile &TileMap::at(int x, int y) {
	return m_tiles[y * sizeX + x];
}

Tile &TileMap::at(sf::Vector2i position) {
	return at(position.x, position.y);
}
