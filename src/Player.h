//
// Created by jngl on 27/04/2020.
//

#ifndef CYBERCRAFT_PLAYER_H
#define CYBERCRAFT_PLAYER_H

#include <SFML/Graphics.hpp>
#include "TileTypeRegistery.h"
#include "TileMap.h"

class Player {
public:
	explicit Player(const TileTypeRegistry& tilesTypes);

	void update(const TileMap& map);

	void draw(sf::RenderTarget& renderTarget);

private:
	sf::Vector2i m_position;
	sf::Sprite m_sprite;
	sf::Clock m_timer;
};


#endif //CYBERCRAFT_PLAYER_H
