//
// Created by jngl on 27/06/2020.
//

#include "Core/Window.h"

Window::Window():
    m_window(sf::VideoMode(800, 600), "Cyber Craft")
{
    m_window.setFramerateLimit(60);
    m_window.setView(m_view);
}

bool Window::isOpen() const {
    return m_window.isOpen();
}

void Window::beginFrame() {
    //input event
    sf::Event event{};
    while (m_window.pollEvent(event)) {
        switch (event.type) {
            case sf::Event::Closed:
                m_window.close();
                break;
            case sf::Event::Resized:
                m_view.setSize(event.size.width, event.size.height);
                m_view.setCenter(static_cast<float>(event.size.width)/2,static_cast<float>(event.size.height)/2);
                m_window.setView(m_view);
                break;
            default:
                break;
        }
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
