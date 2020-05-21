//
// Created by jngl on 27/04/2020.
//

#ifndef CYBERCRAFT_TILETYPEREGISTERY_H
#define CYBERCRAFT_TILETYPEREGISTERY_H

#include "TileType.h"

#include <array>
#include <string>
#include <map>

class TileTypeRegistry {
public:
	TileTypeRegistry();

	const TileType& getType(std::string_view name) const;

	const sf::Texture &getTexture() const;

private:
	std::map<std::string, TileType> m_tiles;
	sf::Texture m_texture;
};


void setSpriteFromTileTypeName(const TileTypeRegistry& registery, sf::Sprite& sprite, std::string_view name);

#endif //CYBERCRAFT_TILETYPEREGISTERY_H
