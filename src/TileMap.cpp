//
// Created by jngl on 27/04/2020.
//

#include "TileMap.h"

#include "Error.h"

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
	Tile* tile = get(position);
	if(!tile){
		throw Error("Out of bound");
	}
	tile->set(m_types, typeName, position);
}

void TileMap::draw(sf::RenderTarget &renderTarget) {
	renderTarget.draw(m_background);
	for (Tile &tile : m_tiles) {
		tile.draw(renderTarget);
	}
}

Tile* TileMap::get(int x, int y) {
	if(x<0 || x>=sizeX || y<0 || x>=sizeY){
		return nullptr;
	}

	return &m_tiles[y * sizeX + x];
}

Tile* TileMap::get(const sf::Vector2i& position) {
	return get(position.x, position.y);
}

const Tile* TileMap::get(int x, int y) const {
	if(x<0 || x>=sizeX || y<0 || y>=sizeY){
		return nullptr;
	}
	return &m_tiles[y * sizeX + x];
}

const Tile* TileMap::get(const sf::Vector2i &position) const {
	return get(position.x, position.y);
}

bool TileMap::isColliding(sf::Vector2i position) const {
	const TileType *type = getType(position.x , position.y);
	if (!type){
		return true;
	}

	return type->getCollision();
}

const TileType *TileMap::getType(int x, int y) const {
	const Tile* tile = get(x, y);
	if(!tile){
		return nullptr;
	}

	return tile->getType();
}
