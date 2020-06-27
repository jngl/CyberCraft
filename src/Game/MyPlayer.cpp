//
// Created by jngl on 27/04/2020.
//

#include "MyPlayer.h"

#include <cmath>
#include "../Core/Math.h"

MyPlayer::MyPlayer(const TileTypeRegistry &types) {
	m_playerComponent.setTileType(types, "player");

	m_cursorComponent.setTileType(types, "cursor");
	m_cursorComponent.setVisible(false);

	m_moveToComponent.setTileType(types, "move to");
	m_moveToComponent.setVisible(false);

	m_view = createDefaultView();
}

void MyPlayer::update(const TileMap& map) {
	movePlayer(map);
	moveViewTo(m_view, m_playerComponent.getWorldPosition(), 1.5f, 10);
}

void MyPlayer::draw(sf::RenderWindow &window) {
	window.setView(m_view);

	m_playerComponent.draw(window);
	m_cursorComponent.draw(window);
	m_moveToComponent.draw(window);

	window.setMouseCursorVisible(!m_cursorComponent.isVisible());
}

sf::Vector2i MyPlayer::getCursorPosition(sf::RenderWindow& window) {
	sf::Vector2i mousePos = sf::Mouse::getPosition(window);
	sf::Vector2f pos = window.mapPixelToCoords(mousePos);

	sf::Vector2i tilePos;
	tilePos.x = std::floor(pos.x/16);
	tilePos.y = std::floor(pos.y/16);

	return tilePos;
}

void MyPlayer::movePlayer(const TileMap& map) {
	m_numberOfTicksForMovement ++;

	if(m_numberOfTicksForMovement<5){
		return;
	}

	if(!m_moveToComponent.isVisible()){
		return;
	}

	sf::Vector2i oldPos = m_playerComponent.getPosition();
	sf::Vector2i newPos = oldPos;

	if(oldPos.x < m_moveToComponent.getPosition().x){
		newPos.x++;
	}else if(oldPos.x > m_moveToComponent.getPosition().x){
		newPos.x--;
	}

	if(oldPos.y < m_moveToComponent.getPosition().y){
		newPos.y++;
	}else if(oldPos.y > m_moveToComponent.getPosition().y){
		newPos.y--;
	}

	if(newPos == oldPos || map.isColliding(newPos)){
		m_moveToComponent.setVisible(false);
	}else{
		m_numberOfTicksForMovement = 0;
        m_playerComponent.setTilePosition(newPos);
	}
}

void MyPlayer::input(const TileMap& map, sf::RenderWindow &window) {
	sf::Vector2i newCursorPos = getCursorPosition(window);

	if(!map.getType(newCursorPos.x, newCursorPos.y)){
		m_cursorComponent.setVisible(false);
		return;
	}

	m_cursorComponent.setVisible(true);
    m_cursorComponent.setTilePosition(newCursorPos);

	if(sf::Mouse::isButtonPressed(sf::Mouse::Left)){
		m_moveToComponent.setVisible(true);
        m_moveToComponent.setTilePosition(newCursorPos);
	}
}
