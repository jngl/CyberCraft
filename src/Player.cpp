//
// Created by jngl on 27/04/2020.
//

#include "Player.h"

#include <cmath>

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
}

void Player::update(const TileMap& map, sf::RenderWindow& window) {
	m_playerSprite.setPosition(static_cast<int>(m_position.x * 16), static_cast<int>(m_position.y * 16));

	sf::Vector2i newCursorPos = getCursorPosition(window);
	if(map.getType(newCursorPos.x, newCursorPos.y)){
		enableCursor(window, newCursorPos);

		if(sf::Mouse::isButtonPressed(sf::Mouse::Left)){
			enableMoveTo(newCursorPos);
		}
	}else{
		disableCursor(window);
	}

	movePlayer(map);
}

void Player::draw(sf::RenderTarget &renderTarget) {
	renderTarget.draw(m_playerSprite);
	if(m_cursorVisible){
		renderTarget.draw(m_cursorSprite);
	}
	if(m_moveToVisible){
		renderTarget.draw(m_moveToSprite);
	}
}

void Player::disableCursor(sf::Window& window) {
	m_cursorVisible = false;
	window.setMouseCursorVisible(true);
}

void Player::enableCursor(sf::Window &window, sf::Vector2i pos) {
	m_cursorSprite.setPosition(pos.x * 16, pos.y * 16);
	window.setMouseCursorVisible(false);
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
	if(m_timer.getElapsedTime().asMilliseconds()<250){
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
		m_timer.restart();
		m_position = newPos;
	}
}
