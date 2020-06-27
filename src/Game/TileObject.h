//
// Created by jngl on 30/05/2020.
//

#ifndef CYBERCRAFT_TILEOBJECT_H
#define CYBERCRAFT_TILEOBJECT_H

#include "../Core/Common.h"

#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics/Sprite.hpp>

class TileObject{
public:
	void draw(sf::RenderWindow& renderTarget);

	void setTileType(const TileTypeRegistry& registry, std::string_view name);

	[[nodiscard]] bool isVisible() const;
	void setVisible(bool v);

	[[nodiscard]] const sf::Vector2i& getPosition() const;
	[[nodiscard]] const sf::Vector2f& getWorldPosition() const;

	void setTilePosition(const sf::Vector2i& pos);

private:
	bool visible = true;
	sf::Sprite sprite;
	sf::Vector2i tilePosition;
};

#endif //CYBERCRAFT_TILEOBJECT_H
