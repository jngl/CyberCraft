#include <SFML/Graphics.hpp>
#include <map>
#include <string>
#include <array>

class Error : public std::exception
{
public:
	Error(std::string_view msg):
	m_message(msg)
	{}

	const char * what() const noexcept override{
		return m_message.c_str();
	}

private:
	std::string m_message;
};

sf::IntRect tilePositionToTextureRect(int x, int y){
	return sf::IntRect(x*17, y*17, 16,16);
}

class TileType{
public:
	TileType(int tileTextureX, int tileTextureY, const sf::Color& color):
	m_textureRect(tilePositionToTextureRect(tileTextureX, tileTextureY)),
	m_color(color)
	{}

	[[nodiscard]] sf::IntRect getTextureRect() const{
		return m_textureRect;
	}

	[[nodiscard]] sf::Color getColor() const{
		return m_color;
	}

private:
	sf::IntRect m_textureRect;
	sf::Color m_color;
};

class TileTypeRegistry{
public:
	TileTypeRegistry(){
		const sf::Color colorPlant(154, 235, 73);
		const sf::Color colorRock(100, 100, 100);
		const sf::Color colorWater(71, 179, 255);
		const sf::Color colorWood(99,64,23);

		m_tiles.emplace("grass", 		TileType{0, 0, colorPlant});
		m_tiles.emplace("long grass",	TileType{5, 0, colorPlant});
		m_tiles.emplace("rock",			TileType{5, 2, colorRock});
		m_tiles.emplace("tree", 			TileType{5, 1, colorPlant});
		m_tiles.emplace("water", 		TileType{8, 5, colorWater});
		m_tiles.emplace("dead bush", 	TileType{6, 2, colorWood});

		if(!m_texture.loadFromFile("../data/tiles.png")){
			throw Error("tiles texture not found");
		}
	}

	TileType getType(std::string_view name) const{
		auto tileType = m_tiles.find(std::string(name));

		if(tileType == m_tiles.end()){
			throw Error("unknown tile");
		}

		return tileType->second;
	}

	const sf::Texture& getTexture() const{
		return m_texture;
	}

private:
	std::map<std::string, TileType> m_tiles;
	sf::Texture m_texture;
};

class Tile{
public:
	void set(const TileTypeRegistry& tiles, std::string_view typeName, sf::Vector2i position){
		const TileType& type = tiles.getType(typeName);

		m_sprite.setTexture(tiles.getTexture());
		m_sprite.setTextureRect(type.getTextureRect());
		m_sprite.setPosition(position.x*16,position.y*16);
		m_sprite.setColor(type.getColor());
	}

	void draw(sf::RenderTarget& renderTarget){
		renderTarget.draw(m_sprite);
	}

private:
	sf::Sprite m_sprite;
};

class TileMap
{
public:
	constexpr static int sizeX = 16;
	constexpr static int sizeY = 16;
	constexpr static std::string_view defaultTileName = "grass";

	explicit TileMap(const TileTypeRegistry& tiles):
			m_types(tiles){
		for(int x(0); x < sizeX; ++x){
			for(int y(0); y < sizeY; ++y){
				set({x, y}, defaultTileName);
			}
		}
	}

	void set(sf::Vector2i position, std::string_view typeName){
		at(position).set(m_types, typeName, position);
	}

	void draw(sf::RenderTarget& renderTarget){
		for(Tile& tile : m_tiles){
			tile.draw(renderTarget);
		}
	}

private:
	std::array<Tile, sizeX * sizeY> m_tiles;
	const TileTypeRegistry& m_types;

	Tile& at(int x, int y){
		return m_tiles[y * sizeX + x];
	}

	Tile& at(sf::Vector2i position){
		return at(position.x, position.y);
	}
};

int main() {
	sf::RenderWindow window(sf::VideoMode(800, 600), "My window");

	TileTypeRegistry types;

	TileMap map(types);
	map.set({1,2}, "long grass");
	map.set({5,7}, "rock");
	map.set({12,9}, "tree");
	map.set({15,14}, "water");
	map.set({3,14}, "dead bush");

	sf::View view(sf::FloatRect(-16.f, -16.f, 400.f, 300.f));
	window.setView(view);

	while (window.isOpen()) {
		sf::Event event{};
		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed)
				window.close();
		}

		window.clear({0,150,0});

		map.draw(window);

		window.display();
	}

	return 0;
}
