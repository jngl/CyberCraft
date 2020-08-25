//
// Created by jngl on 18/07/2020.
//

#ifndef CYBERCRAFT_SYSTEM_H
#define CYBERCRAFT_SYSTEM_H

#include "Common.h"

void drawSprite(Window& win, const sf::Texture& texture, const sf::Vector2f& pos, const component::Sprite& sprite);
void movePlayer(sf::Vector2f & pos, component::Player& player, const World& world);

#endif //CYBERCRAFT_SYSTEM_H
