//
// Created by jngl on 27/04/2020.
//

#ifndef CYBERCRAFT_MYPLAYER_H
#define CYBERCRAFT_MYPLAYER_H

#include <SFML/Graphics.hpp>

#include "../BasicWorld/Camera.h"
#include "TileObject.h"

#include "../BasicWorld/Player.h"
#include "../BasicWorld/Map.h"

class MyPlayer : public Player {
public:
	explicit MyPlayer(const TileTypeRegistry& tilesTypes);

	void input(const TileMap& map, sf::RenderWindow& window) override;
	void update(const TileMap& map) override;
	void draw(sf::RenderWindow& renderTarget) override;

private:
	int m_numberOfTicksForMovement = 0;
	sf::View m_view;

	TileObject m_moveToComponent;
	TileObject m_cursorComponent;
	TileObject m_playerComponent;

	void movePlayer(const TileMap& map);

	static sf::Vector2i getCursorPosition(sf::RenderWindow& window);
};


#endif //CYBERCRAFT_MYPLAYER_H
