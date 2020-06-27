//
// Created by jngl on 27/06/2020.
//

#include "Map.h"

#include <SFML/Graphics/Sprite.hpp>

sf::IntRect TileType::getTextureRect() const {
    return sf::IntRect(textureTileIndex.x * 17, textureTileIndex.y * 17, 16, 16);
}

sf::Sprite TileTypeRegistry::setSpriteFromTileTypeName(std::string_view name) const{
    sf::Sprite sprite;

    const TileType& type = getType(name);

    sprite.setTexture(getTexture());
    sprite.setTextureRect(type.getTextureRect());
    sprite.setColor(type.color);

    return sprite;
}