//
// Created by jngl on 27/04/2020.
//

#include "Tile.h"

void Tile::set(const TileTypeRegistry &tiles, std::string_view typeName, sf::Vector2i position) {
	const TileType &type = tiles.getType(typeName);

	m_sprite.setTexture(tiles.getTexture());
	m_sprite.setTextureRect(type.getTextureRect());
	m_sprite.setPosition(position.x * 16, position.y * 16);
	m_sprite.setColor(type.getColor());
}

void Tile::draw(sf::RenderTarget &renderTarget) {
	renderTarget.draw(m_sprite);
}
