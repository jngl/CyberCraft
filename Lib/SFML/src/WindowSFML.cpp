//
// Created by jngl on 29/08/2020.
//

#include "CyberCraftSFML/WindowSFML.h"

#include <SFML/Window/Event.hpp>

#include "conversion.h"

#include <Core/Color.h>

constexpr int defaultWindowSizeX = 800;
constexpr int defaultWindowSizeY = 600;
constexpr int defaultFrameRate = 60;

namespace ccSf {
    bool WindowSFML::isOpen() const {
        return m_window.isOpen();
    }

    void WindowSFML::beginFrame() {
        //input event
        sf::Event event{};
        while (m_window.pollEvent(event)) {
            switch (event.type) {
                case sf::Event::Closed:
                    m_window.close();
                    break;
                case sf::Event::Resized: {
                    sf::View view(m_window.getView());
                    view.setSize(static_cast<float>(event.size.width), static_cast<float>(event.size.height));  // NOLINT
                    m_window.setView(view);
                    break;
                }
                default:
                    break;
            }
        }

        //clear
        m_window.clear(sf::Color::Black);
    }

    void WindowSFML::endFrame() {
        m_window.display();
    }

    WindowSFML::WindowSFML() :
            m_window(sf::VideoMode(defaultWindowSizeX, defaultWindowSizeY), "Cyber Craft") {
        m_window.setFramerateLimit(defaultFrameRate);
    }

    sf::RenderWindow &WindowSFML::getRenderWindow() {
        return m_window;
    }

    WindowSFML::~WindowSFML() = default;
}