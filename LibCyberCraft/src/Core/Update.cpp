//
// Created by jngl on 18/07/2020.
//

#include "Core/Update.h"

FixStepUpdater::FixStepUpdater(sf::Time timePerUpdate):
m_timePerUpdate(timePerUpdate){
    m_previous  = m_frameClock.getElapsedTime();
}

