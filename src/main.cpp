#include <SFML/Graphics.hpp>

int main() {
	sf::RenderWindow window(sf::VideoMode(800, 600), "My window");

	sf::RectangleShape rect;
	rect.setSize(sf::Vector2f(100,100));
	rect.setPosition(100,100);

	while (window.isOpen()) {
		sf::Event event;
		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed)
				window.close();
		}

		window.clear(sf::Color::Black);

		window.draw(rect);

		window.display();
	}

	return 0;
}
