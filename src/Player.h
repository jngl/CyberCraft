//
// Created by jngl on 27/04/2020.
//

#ifndef CYBERCRAFT_PLAYER_H
#define CYBERCRAFT_PLAYER_H

#include <SFML/Graphics.hpp>

#include "TileTypeRegistry.h"
#include "TileMap.h"
#include "Camera.h"
#include "TileObject.h"

class Player {
public:
	explicit Player(const TileTypeRegistry& tilesTypes);

	void input(const TileMap& map, sf::RenderWindow& window);
	void update(const TileMap& map);
	void draw(sf::RenderWindow& renderTarget);

private:
	int m_numberOfTicksForMovement = 0;
	sf::View m_view;

	TileObject m_moveToComponent;
	TileObject m_cursorComponent;
	TileObject m_playerComponent;

	void movePlayer(const TileMap& map);

	static sf::Vector2i getCursorPosition(sf::RenderWindow& window);
};


#endif //CYBERCRAFT_PLAYER_H
