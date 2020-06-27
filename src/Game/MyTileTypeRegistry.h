//
// Created by jngl on 27/04/2020.
//

#ifndef CYBERCRAFT_MYTILETYPEREGISTRY_H
#define CYBERCRAFT_MYTILETYPEREGISTRY_H

#include "../Core/Common.h"
#include "../BasicWorld/Map.h"

#include <map>
#include <SFML/Graphics/Texture.hpp>

class MyTileTypeRegistry : public TileTypeRegistry {
public:
	MyTileTypeRegistry();

	[[nodiscard]] const TileType& getType(std::string_view name) const override ;

	[[nodiscard]] const sf::Texture &getTexture() const override;

private:
	std::map<std::string, TileType> m_tiles;
	sf::Texture m_texture;
};



#endif //CYBERCRAFT_MYTILETYPEREGISTRY_H
