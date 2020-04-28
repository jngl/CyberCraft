//
// Created by jngl on 27/04/2020.
//

#include "Player.h"

#include <cmath>
#include "Math.h"

Player::Player(const TileTypeRegistry &types) {
	const TileType& type = types.getType("player");
	m_playerSprite.setTexture(types.getTexture());
	m_playerSprite.setTextureRect(type.getTextureRect());
	m_playerSprite.setColor(type.getColor());

	const TileType& cursorType = types.getType("cursor");
	m_cursorSprite.setTexture(types.getTexture());
	m_cursorSprite.setTextureRect(cursorType.getTextureRect());
	m_cursorSprite.setColor(cursorType.getColor());

	const TileType& typeMoveTo = types.getType("move to");
	m_moveToSprite.setTexture(types.getTexture());
	m_moveToSprite.setTextureRect(typeMoveTo.getTextureRect());
	m_moveToSprite.setColor(typeMoveTo.getColor());

	m_view.setSize(400,300);
	m_view.setCenter(sf::Vector2f());
}

void Player::update(const TileMap& map) {
	m_playerSprite.setPosition(static_cast<int>(m_position.x * 16), static_cast<int>(m_position.y * 16));

	movePlayer(map);

	moveView();
}

void Player::draw(sf::RenderWindow &window) {
	window.setView(m_view);

	window.draw(m_playerSprite);
	if(m_cursorVisible){
		window.draw(m_cursorSprite);
	}
	if(m_moveToVisible){
		window.draw(m_moveToSprite);
	}
	window.setMouseCursorVisible(!m_cursorVisible);
}

void Player::disableCursor() {
	m_cursorVisible = false;
}

void Player::enableCursor(sf::Vector2i pos) {
	m_cursorSprite.setPosition(pos.x * 16, pos.y * 16);
	m_cursorVisible = true;
}

void Player::enableMoveTo(sf::Vector2i pos) {
	m_moveToVisible = true;
	m_moveToSprite.setPosition(pos.x * 16, pos.y * 16);
	m_moveTo = pos;
}

sf::Vector2i Player::getCursorPosition(sf::RenderWindow& window) {
	sf::Vector2i mousePos = sf::Mouse::getPosition(window);
	sf::Vector2f pos = window.mapPixelToCoords(mousePos);

	sf::Vector2i tilePos;
	tilePos.x = std::floor(pos.x/16);
	tilePos.y = std::floor(pos.y/16);

	return tilePos;
}

void Player::disableMoveTo() {
	m_moveToVisible = false;
}

void Player::movePlayer(const TileMap& map) {
	m_numberOfTicksForMovement ++;

	if(m_numberOfTicksForMovement<5){
		return;
	}

	if(!m_moveToVisible){
		return;
	}

	sf::Vector2i newPos = m_position;

	if(m_position.x < m_moveTo.x){
		newPos.x++;
	}else if(m_position.x > m_moveTo.x){
		newPos.x--;
	}

	if(m_position.y < m_moveTo.y){
		newPos.y++;
	}else if(m_position.y > m_moveTo.y){
		newPos.y--;
	}

	if(newPos == m_position || map.isColliding(newPos)){
		disableMoveTo();
	}else{
		m_numberOfTicksForMovement = 0;
		m_position = newPos;
	}
}

void Player::moveView() {
	const sf::Vector2f& center = m_view.getCenter();

	sf::Vector2f diff = m_playerSprite.getPosition() - center;
	float length = math::length(diff);

	sf::Vector2f move;

	if(length>3.f){
		move = diff / length * 3.f;
	}

	m_view.setCenter(center + move);
}

void Player::input(const TileMap& map, sf::RenderWindow &window) {
	sf::Vector2i newCursorPos = getCursorPosition(window);
	if(map.getType(newCursorPos.x, newCursorPos.y)){
		enableCursor(newCursorPos);

		if(sf::Mouse::isButtonPressed(sf::Mouse::Left)){
			enableMoveTo(newCursorPos);
		}
	}else{
		disableCursor();
	}
}
