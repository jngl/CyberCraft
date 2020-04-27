//
// Created by jngl on 27/04/2020.
//

#ifndef CYBERCRAFT_TILEMAP_H
#define CYBERCRAFT_TILEMAP_H

#include "TileTypeRegistery.h"
#include "Tile.h"

class TileMap {
public:
	constexpr static int sizeX = 16;
	constexpr static int sizeY = 16;
	constexpr static std::string_view defaultTileName = "grass";

	explicit TileMap(const TileTypeRegistry &tiles);

	void set(sf::Vector2i position, std::string_view typeName);

	void draw(sf::RenderTarget &renderTarget);

private:
	std::array<Tile, sizeX * sizeY> m_tiles;
	const TileTypeRegistry &m_types;

	Tile &at(int x, int y);

	Tile &at(sf::Vector2i position);
};

#endif //CYBERCRAFT_TILEMAP_H
