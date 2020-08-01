//
// Created by jngl on 18/07/2020.
//

#ifndef CYBERCRAFT_UPDATE_H
#define CYBERCRAFT_UPDATE_H

#include <memory>
#include <SFML/System/Clock.hpp>
#include <SFML/System/Time.hpp>

class FixStepUpdater
{
public:
    explicit FixStepUpdater(sf::Time timePerUpdate);

    template<class Callable>
    void update(Callable func){
        sf::Time current = m_frameClock.getElapsedTime();
        sf::Time elapsed = current - m_previous;
        m_previous = current;
        m_lag += elapsed;

        while(m_lag >= m_timePerUpdate){
            func();
            m_lag -= m_timePerUpdate;
        }
    }

private:
    sf::Clock m_frameClock;
    sf::Time m_previous;
    sf::Time m_lag;

    sf::Time m_timePerUpdate;
};


#endif //CYBERCRAFT_UPDATE_H
