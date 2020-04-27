//
// Created by jngl on 27/04/2020.
//

#ifndef CYBERCRAFT_TILE_H
#define CYBERCRAFT_TILE_H

#include "TileTypeRegistery.h"

class Tile {
public:
	void set(const TileTypeRegistry &tiles, std::string_view typeName, sf::Vector2i position);

	void draw(sf::RenderTarget &renderTarget);

private:
	sf::Sprite m_sprite;
};

#endif //CYBERCRAFT_TILE_H
