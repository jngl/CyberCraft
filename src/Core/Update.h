//
// Created by jngl on 18/07/2020.
//

#ifndef CYBERCRAFT_UPDATE_H
#define CYBERCRAFT_UPDATE_H

#include <memory>
#include <SFML/System/Clock.hpp>
#include <SFML/System/Time.hpp>

class WithFixTimeUpdate
{
public:
    virtual void update() = 0;
};

class FixStepUpdater
{
public:
    explicit FixStepUpdater(sf::Time timePerUpdate);

    void update(WithFixTimeUpdate& object);

private:
    sf::Clock m_frameClock;
    sf::Time m_previous;
    sf::Time m_lag;

    sf::Time m_timePerUpdate;
};


#endif //CYBERCRAFT_UPDATE_H
