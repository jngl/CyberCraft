//
// Created by jngl on 29/08/2020.
//

#include "CyberCraftSFML/WindowSFML.h"

#include <SFML/Window/Event.hpp>

#include "conversion.h"

#include <Core/Color.h>
#include <SFML/Graphics/VertexArray.hpp>

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

    bool WindowSFML::isKeyPressed(ck::Key key) {
        auto convKey  = [](ck::Key ckKey) -> sf::Keyboard::Key{
            switch(ckKey){
                case ck::Key::LEFT:
                    return sf::Keyboard::Left;
                case ck::Key::RIGHT:
                    return sf::Keyboard::Right;
                case ck::Key::UP:
                    return sf::Keyboard::Up;
                case ck::Key::DOWN:
                    return sf::Keyboard::Down;
                default:
                    return sf::Keyboard::KeyCount;
            }
        };

        return sf::Keyboard::isKeyPressed(convKey(key));
    }

    void WindowSFML::processEvent(ck::ExitListener &exitListener, ck::KeyListener &keyListener) {
        // TODO
    }

    cc::Vector2ui WindowSFML::getSize() const {
        return {m_window.getSize().x, m_window.getSize().y};
    }

    WindowSFML::~WindowSFML() = default;
}