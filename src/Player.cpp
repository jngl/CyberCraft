//
// Created by jngl on 27/04/2020.
//

#include "Player.h"

Player::Player(const TileTypeRegistry &types) {
	const TileType& type = types.getType("player");

	m_sprite.setTexture(types.getTexture());
	m_sprite.setTextureRect(type.getTextureRect());
	m_sprite.setColor(type.getColor());
}

void Player::update(const TileMap& map) {
	if(m_timer.getElapsedTime().asMilliseconds()>250){
		sf::Vector2i move{};

		if(sf::Keyboard::isKeyPressed(sf::Keyboard::Down)){
			move.y++;
		}
		if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up)){
			move.y--;
		}
		if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right)){
			move.x++;
		}
		if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left)){
			move.x--;
		}

		if(move != sf::Vector2i()){
			sf::Vector2i newPos = m_position + move;
			if(!map.isColliding(newPos)){
				m_timer.restart();
				m_position = newPos;
			}
		}
	}

	m_sprite.setPosition(static_cast<int>(m_position.x*16), static_cast<int>(m_position.y*16));
}

void Player::draw(sf::RenderTarget &renderTarget) {
	renderTarget.draw(m_sprite);
}
