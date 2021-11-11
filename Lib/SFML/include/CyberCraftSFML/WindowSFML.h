//
// Created by jngl on 29/08/2020.
//

#ifndef CYBERCRAFT_WINDOWSFML_H
#define CYBERCRAFT_WINDOWSFML_H

#include <Ports/Window.h>
#include <SFML/Graphics/RenderWindow.hpp>

namespace ccSf {
    class WindowSFML : public cp::Window {
    public:
        WindowSFML();

        ~WindowSFML() override;

        [[nodiscard]] bool isOpen() const override;

        void beginFrame() override;

        void endFrame() override;

        sf::RenderWindow &getRenderWindow();

        bool isKeyPressed(cp::Key key) override;

        [[nodiscard]] cc::Vector2ui getSize() const override;

    private:
        sf::RenderWindow m_window;
    };
}

#endif //CYBERCRAFT_WINDOWSFML_H
