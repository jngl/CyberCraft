//
// Created by jngl on 18/07/2020.
//

#ifndef CYBERCRAFT_COMPONENT_H
#define CYBERCRAFT_COMPONENT_H

#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics/Color.hpp>

namespace component{
    struct Sprite{
        sf::Vector2i textureIndex;
        sf::Color color;
        sf::Color backgroundColor;
    };
    struct Player{
        int timerMove;
    };
}


#endif //CYBERCRAFT_COMPONENT_H
