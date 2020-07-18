//
// Created by jngl on 27/06/2020.
//

#include "Window.h"

Window::Window():
    m_window(sf::VideoMode(800, 600), "Cyber Craft")
{
    m_window.setFramerateLimit(60);
}

bool Window::isOpen() const {
    return m_window.isOpen();
}

void Window::beginFrame() {
    //input event
    sf::Event event{};
    while (m_window.pollEvent(event)) {
        if (event.type == sf::Event::Closed)
            m_window.close();
    }

    //clear
    m_window.clear(sf::Color::Black);
}

void Window::endFrame() {
    m_window.display();
}

sf::RenderWindow &Window::getSFMLWindowsRef() {
    return m_window;
}
