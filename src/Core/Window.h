//
// Created by jngl on 27/06/2020.
//

#ifndef CYBERCRAFT_WINDOW_H
#define CYBERCRAFT_WINDOW_H

#include <SFML/Graphics.hpp>

class Window {
public:
    Window();

    [[nodiscard]] bool isOpen() const;

    void beginFrame();
    void endFrame();

    sf::RenderWindow& getSFMLWindowsRef();

    template<class Func>
    void update(Func func){
        const sf::Time timePerUpdate = sf::milliseconds(33);

        while(m_lag >= timePerUpdate){
            func();
            m_lag -= timePerUpdate;
        }
    }

private:
    sf::RenderWindow m_window;

    sf::Clock m_frameClock;
    sf::Time m_previous;
    sf::Time m_lag;
};


#endif //CYBERCRAFT_WINDOW_H
