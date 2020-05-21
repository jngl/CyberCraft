//
// Created by jngl on 27/04/2020.
//

#include "Error.h"
#include "TileTypeRegistery.h"

TileTypeRegistry::TileTypeRegistry() {
	const sf::Color colorPlant(154, 235, 73);
	const sf::Color colorRock(100, 100, 100);
	const sf::Color colorWater(71, 179, 255);
	const sf::Color colorWood(99, 64, 23);
	const sf::Color colorPlayer(255,255,255);

	m_tiles.emplace("grass", TileType{0, 0, colorPlant, false});
	m_tiles.emplace("long grass", TileType{5, 0, colorPlant, false});
	m_tiles.emplace("rock", TileType{5, 2, colorRock, true});
	m_tiles.emplace("tree", TileType{0, 1, colorPlant, true});
	m_tiles.emplace("water", TileType{8, 5, colorWater, true});
	m_tiles.emplace("dead bush", TileType{6, 2, colorWood, false});
	m_tiles.emplace("player", TileType{25, 0, colorPlayer, true});
	m_tiles.emplace("cursor", TileType{29, 14, colorPlayer, false});
	m_tiles.emplace("move to", TileType{30, 14, colorPlayer, false});


	if (!m_texture.loadFromFile("../data/tiles.png")) {
		throw Error("tiles texture not found");
	}
}

const TileType& TileTypeRegistry::getType(std::string_view name) const {
	auto tileType = m_tiles.find(std::string(name));

	if (tileType == m_tiles.end()) {
		throw Error("unknown tile");
	}

	return tileType->second;
}

const sf::Texture &TileTypeRegistry::getTexture() const {
	return m_texture;
}

void setSpriteFromTileTypeName(const TileTypeRegistry& registery, sf::Sprite& sprite, std::string_view name){
	const TileType& type = registery.getType(name);
	sprite.setTexture(registery.getTexture());
	sprite.setTextureRect(type.getTextureRect());
	sprite.setColor(type.getColor());
}