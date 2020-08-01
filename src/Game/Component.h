//
// Created by jngl on 18/07/2020.
//

#ifndef CYBERCRAFT_COMPONENT_H
#define CYBERCRAFT_COMPONENT_H

#include <SFML/Graphics.hpp>

struct PositionComponent{
    sf::Vector2f position;
};

struct SpriteComponent{
    const sf::Texture* texture = nullptr;
    sf::Vector2i textureIndex;
    sf::Color color;
};

struct PlayerComponent{
};

#endif //CYBERCRAFT_COMPONENT_H
