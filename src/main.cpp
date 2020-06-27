#include <SFML/Graphics.hpp>

#include "TileTypeRegistry.h"
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

	//frame clock
	sf::Clock frameClock;
	sf::Time previous  = frameClock.getElapsedTime();
	sf::Time lag;

	const sf::Time timePerUpdate = sf::milliseconds(33);

	while (window.isOpen()) {
		//frame clock update
		sf::Time current = frameClock.getElapsedTime();
		sf::Time elapsed = current - previous;
		previous = current;
		lag += elapsed;

		//input event
		sf::Event event{};
		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed)
				window.close();
		}

		player.input(map, window);

		//update
		while(lag >= timePerUpdate){
			player.update(map);
			lag -= timePerUpdate;
		}

		//render
		window.clear(sf::Color::Black);

		map.draw(window);
		player.draw(window);

		window.display();
	}

	return 0;
}
