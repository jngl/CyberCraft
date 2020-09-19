//
// Created by jngl on 29/08/2020.
//

#include "CyberCraftSFML/WindowSFML.h"

#include <SFML/Window/Event.hpp>

#include "conversion.h"

#include <Core/Color.h>

bool WindowSFML::isOpen() const {
    return m_window.isOpen();
}

void WindowSFML::beginFrame(){
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
void WindowSFML::endFrame(){
    m_window.display();
}

WindowSFML::WindowSFML():
        m_window(sf::VideoMode(800, 600), "Cyber Craft")
{
    m_window.setFramerateLimit(60);
    m_window.setView(m_view);
}

sf::RenderWindow &WindowSFML::getRenderWindow() {
    return m_window;
}

WindowSFML::~WindowSFML() = default;

