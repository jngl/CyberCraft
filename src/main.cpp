#include <SFML/Graphics.hpp>

#include "Game/MyPlayer.h"
#include "Game/MyTileTypeRegistry.h"
#include "Game/MyTileMap.h"

int main() {
	sf::RenderWindow window(sf::VideoMode(800, 600), "My window");
	window.setFramerateLimit(60);

    MyTileTypeRegistry types;
    MyPlayer player(types);

    MyTileMap map(types);
    map.set({5,5}, "long grass");
    map.set({15,5}, "rock");
    map.set({5,15}, "tree");
    map.set({15,15}, "water");
    map.set({7,12}, "dead bush");

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
