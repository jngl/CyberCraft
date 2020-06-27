//
// Created by jngl on 27/04/2020.
//

#ifndef CYBERCRAFT_MYTILEMAP_H
#define CYBERCRAFT_MYTILEMAP_H

#include "../Core/Common.h"
#include "../BasicWorld/Map.h"

#include "Tile.h"
#include <SFML/Graphics/RectangleShape.hpp>

class MyTileMap : public TileMap {
public:
	constexpr static int sizeX = 32;
	constexpr static int sizeY = 32;
	constexpr static std::string_view defaultTileName = "grass";

	explicit MyTileMap(const TileTypeRegistry &tiles);

	void set(sf::Vector2i position, std::string_view typeName);

	[[nodiscard]] const TileType* getType(int x, int y) const override;

	void draw(sf::RenderTarget &renderTarget) override;

	[[nodiscard]] bool isColliding(sf::Vector2i position) const override;

private:
	std::array<Tile, sizeX * sizeY> m_tiles;
	const TileTypeRegistry &m_types;
	sf::RectangleShape m_background;

	Tile *get(int x, int y);
	Tile *get(const sf::Vector2i& position);

	const Tile *get(int x, int y) const;
	const Tile *get(const sf::Vector2i& position) const;

};

#endif //CYBERCRAFT_MYTILEMAP_H
