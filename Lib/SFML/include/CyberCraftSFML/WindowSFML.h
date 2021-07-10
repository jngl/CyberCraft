//
// Created by jngl on 29/08/2020.
//

#ifndef CYBERCRAFT_WINDOWSFML_H
#define CYBERCRAFT_WINDOWSFML_H

#include <Kernel/Window.h>
#include <SFML/Graphics/RenderWindow.hpp>

namespace ccSf {
<<<<<<< HEAD:Lib/SFML/include/CyberCraftSFML/WindowSFML.h
    class WindowSFML : public ck::Window {
=======
    class WindowSFML : public cc::Window {
>>>>>>> b0d8808aab9721dbaa8c9afaf9c8a706f1faee8f:LibCyberCraftSFML/include/CyberCraftSFML/WindowSFML.h
    public:
        WindowSFML();

        ~WindowSFML() override;

        [[nodiscard]] bool isOpen() const override;

        void beginFrame() override;

        void endFrame() override;

        sf::RenderWindow &getRenderWindow();

    private:
        sf::RenderWindow m_window;
    };
}

#endif //CYBERCRAFT_WINDOWSFML_H
