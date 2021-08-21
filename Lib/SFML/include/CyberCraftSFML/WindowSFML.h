//
// Created by jngl on 29/08/2020.
//

#ifndef CYBERCRAFT_WINDOWSFML_H
#define CYBERCRAFT_WINDOWSFML_H

#include <Kernel/Window.h>
#include <SFML/Graphics/RenderWindow.hpp>

namespace ccSf {
    class WindowSFML : public ck::Window {
    public:
        WindowSFML();

        ~WindowSFML() override;

        [[nodiscard]] bool isOpen() const override;

        void beginFrame() override;

        void endFrame() override;

        sf::RenderWindow &getRenderWindow();

        bool isKeyPressed(ck::Key key) override;

    private:
        sf::RenderWindow m_window;
    };
}

#endif //CYBERCRAFT_WINDOWSFML_H
