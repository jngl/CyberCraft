//
// Created by jngl on 27/04/2020.
//

#include "Tile.h"

#include "../BasicWorld/Map.h"

#include <SFML/Graphics/RenderTarget.hpp>

void Tile::set(const TileTypeRegistry &tiles, std::string_view typeName, sf::Vector2i position){
	m_type = &tiles.getType(typeName);

	m_sprite.setTexture(tiles.getTexture());
	m_sprite.setTextureRect(m_type->getTextureRect());
	m_sprite.setPosition(position.x * 16, position.y * 16);
	m_sprite.setColor(m_type->color);
}

void Tile::draw(sf::RenderTarget &renderTarget) {
	if(m_type){
		renderTarget.draw(m_sprite);
	}
}

const TileType *Tile::getType() const {
	return m_type;
}
