//
// Created by jngl on 30/05/2020.
//

#ifndef CYBERCRAFT_TILEOBJECT_H
#define CYBERCRAFT_TILEOBJECT_H

#include <SFML/Graphics.hpp>

class TileTypeRegistry;

class TileObject{
public:
	void draw(sf::RenderWindow& renderTarget);

	void setTileType(const TileTypeRegistry& registry, std::string_view name);

	bool isVisible() const;
	void setVisible(bool v);

	const sf::Vector2i& getPosition() const;
	const sf::Vector2f& getWorldPosition() const;

	void setTilePosition(const sf::Vector2i& pos);
	void setWorldPosition(const sf::Vector2f& pos);

private:
	bool visible = true;
	sf::Sprite sprite;
	sf::Vector2i tilePosition;
};

#endif //CYBERCRAFT_TILEOBJECT_H
