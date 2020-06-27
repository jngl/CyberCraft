//
// Created by jngl on 27/04/2020.
//

#ifndef CYBERCRAFT_TILETYPEREGISTRY_H
#define CYBERCRAFT_TILETYPEREGISTRY_H

#include <SFML/Graphics.hpp>

#include <array>
#include <string>
#include <map>

struct TileType {
    sf::Vector2i textureTileIndex;
    sf::Color color;
    bool collision = false;

    [[nodiscard]] sf::IntRect getTextureRect() const;
};

class TileTypeRegistry {
public:
	TileTypeRegistry();

	const TileType& getType(std::string_view name) const;

	const sf::Texture &getTexture() const;

    void setSpriteFromTileTypeName(sf::Sprite& sprite, std::string_view name) const;

private:
	std::map<std::string, TileType> m_tiles;
	sf::Texture m_texture;
};



#endif //CYBERCRAFT_TILETYPEREGISTRY_H
