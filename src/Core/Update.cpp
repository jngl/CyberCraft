//
// Created by jngl on 18/07/2020.
//

#include "Update.h"

FixStepUpdater::FixStepUpdater(sf::Time timePerUpdate):
m_timePerUpdate(timePerUpdate){
    m_previous  = m_frameClock.getElapsedTime();
}

void FixStepUpdater::update(WithFixTimeUpdate &object) {
    sf::Time current = m_frameClock.getElapsedTime();
    sf::Time elapsed = current - m_previous;
    m_previous = current;
    m_lag += elapsed;

    while(m_lag >= m_timePerUpdate){
        object.update();
        m_lag -= m_timePerUpdate;
    }
}
