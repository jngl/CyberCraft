//
// Created by jngl on 27/04/2020.
//

#ifndef CYBERCRAFT_TILETYPE_H
#define CYBERCRAFT_TILETYPE_H

#include <SFML/Graphics.hpp>

class TileType {
public:
	TileType(int tileTextureX, int tileTextureY, const sf::Color &color);

	[[nodiscard]] sf::IntRect getTextureRect() const;

	[[nodiscard]] sf::Color getColor() const;

private:
	sf::IntRect m_textureRect;
	sf::Color m_color;

	static sf::IntRect tilePositionToTextureRect(int x, int y);
};

#endif //CYBERCRAFT_TILETYPE_H
