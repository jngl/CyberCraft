//
// Created by jngl on 27/04/2020.
//

#include "TileType.h"

TileType::TileType(int tileTextureX, int tileTextureY, const sf::Color &color, bool collision) :
		m_textureRect(tilePositionToTextureRect(tileTextureX, tileTextureY)),
		m_color(color),
		m_collision(collision){

}

sf::IntRect TileType::getTextureRect() const {
	return m_textureRect;
}

sf::Color TileType::getColor() const {
	return m_color;
}

sf::IntRect TileType::tilePositionToTextureRect(int x, int y) {
	return sf::IntRect(x * 17, y * 17, 16, 16);
}

bool TileType::getCollision() const {
	return m_collision;
}
