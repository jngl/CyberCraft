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

	void input(const TileMap& map, sf::RenderWindow& renderTarge);
	void update(const TileMap& map);
	void draw(sf::RenderWindow& renderTarget);

private:
	sf::Vector2i m_position;
	int m_numberOfTicksForMovement = 0;
	sf::Sprite m_playerSprite;
	sf::Sprite m_cursorSprite;
	sf::Sprite m_moveToSprite;
	bool m_cursorVisible = false;
	bool m_moveToVisible = false;
	sf::Vector2i m_moveTo;
	sf::View m_view;

	void disableCursor();
	void enableCursor(sf::Vector2i pos);

	void disableMoveTo();
	void enableMoveTo(sf::Vector2i pos);

	void movePlayer(const TileMap& map);

	void moveView();

	static sf::Vector2i getCursorPosition(sf::RenderWindow& window);
};


#endif //CYBERCRAFT_PLAYER_H
