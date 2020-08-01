//
// Created by jngl on 27/06/2020.
//

#ifndef CYBERCRAFT_WINDOW_H
#define CYBERCRAFT_WINDOW_H

#include "Scene.h"

#include <SFML/Graphics.hpp>

class Window {
public:
    Window();

    [[nodiscard]] bool isOpen() const;

    void beginFrame();
    void endFrame();

    sf::RenderWindow& getSFMLWindowsRef();

private:
    sf::RenderWindow m_window;
};


#endif //CYBERCRAFT_WINDOW_H
