//
// Created by jngl on 30/05/2020.
//

#include "TileObject.h"

#include "MyTileTypeRegistry.h"
#include <SFML/Graphics/RenderWindow.hpp>

void TileObject::draw(sf::RenderWindow &renderTarget) {
	if(visible){
		renderTarget.draw(sprite);
	}
}

void TileObject::setTileType(const TileTypeRegistry &registry, std::string_view name) {
    sprite = registry.setSpriteFromTileTypeName(name);
}

bool TileObject::isVisible() const {
	return visible;
}

const sf::Vector2i &TileObject::getPosition() const {
	return tilePosition;
}

void TileObject::setTilePosition(const sf::Vector2i &pos) {
	tilePosition = pos;
	sprite.setPosition(static_cast<float>(tilePosition.x) * 16.f, static_cast<float>(tilePosition.y) * 16.f);
}

void TileObject::setVisible(bool v) {
	visible = v;
}

const sf::Vector2f &TileObject::getWorldPosition() const {
	return sprite.getPosition();
}
