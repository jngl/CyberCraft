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

	void update(const TileMap& map, sf::RenderWindow& window);

	void draw(sf::RenderTarget& renderTarget);

private:
	sf::Vector2i m_position;
	sf::Clock m_timer;
	sf::Sprite m_playerSprite;
	sf::Sprite m_cursorSprite;
	sf::Sprite m_moveToSprite;
	bool m_cursorVisible = false;
	bool m_moveToVisible = false;
	sf::Vector2i m_moveTo;

	void disableCursor(sf::Window& window);
	void enableCursor(sf::Window& window, sf::Vector2i pos);

	void disableMoveTo();
	void enableMoveTo(sf::Vector2i pos);

	void movePlayer(const TileMap& map);

	static sf::Vector2i getCursorPosition(sf::RenderWindow& window);
};


#endif //CYBERCRAFT_PLAYER_H
