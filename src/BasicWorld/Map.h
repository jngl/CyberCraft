//
// Created by jngl on 27/06/2020.
//

#ifndef CYBERCRAFT_MAP_H
#define CYBERCRAFT_MAP_H

#include "../Core/Common.h"

#include <SFML/Graphics/Color.hpp>
#include <SFML/System/Vector2.hpp>

struct TileType {
    sf::Vector2i textureTileIndex;
    sf::Color color;
    bool collision = false;

    [[nodiscard]] sf::IntRect getTextureRect() const;
};

class TileTypeRegistry {
public:
    virtual ~TileTypeRegistry() = default;

    virtual const TileType& getType(std::string_view name) const = 0;
    virtual const sf::Texture &getTexture() const = 0;

    [[nodiscard]] sf::Sprite setSpriteFromTileTypeName(std::string_view name) const;
};

class TileMap {
public:
    virtual ~TileMap() = default;

    [[nodiscard]] virtual const TileType* getType(int x, int y) const = 0;
    virtual void draw(sf::RenderTarget &renderTarget) = 0;
    [[nodiscard]] virtual bool isColliding(sf::Vector2i position) const = 0;
};

#endif //CYBERCRAFT_MAP_H
