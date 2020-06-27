//
// Created by jngl on 27/06/2020.
//

#ifndef CYBERCRAFT_PLAYER_H
#define CYBERCRAFT_PLAYER_H

#include "../Core/Common.h"

class Player{
public:
    virtual ~Player() = default;

    virtual void input(const TileMap& map, sf::RenderWindow& window) = 0;
    virtual void update(const TileMap& map) = 0;
    virtual void draw(sf::RenderWindow& renderTarget) = 0;
};

#endif //CYBERCRAFT_PLAYER_H
