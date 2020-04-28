#include <SFML/Graphics.hpp>

#include "TileTypeRegistery.h"
#include "TileMap.h"
#include "Player.h"

int main() {
	sf::RenderWindow window(sf::VideoMode(800, 600), "My window");
	window.setFramerateLimit(60);

	TileTypeRegistry types;

	TileMap map(types);
	map.set({1, 2}, "long grass");
	map.set({5, 7}, "rock");
	map.set({12, 9}, "tree");
	map.set({15, 14}, "water");
	map.set({3, 14}, "dead bush");

	Player player(types);

	while (window.isOpen()) {
		sf::Event event{};
		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed)
				window.close();
		}

		window.clear(sf::Color::Black);

		map.draw(window);

		player.update(map, window);
		player.draw(window);

		window.display();
	}

	return 0;
}
