//
// Created by jngl on 18/07/2020.
//

#include "Core/Update.h"

FixStepUpdater::FixStepUpdater(const Duration& timePerUpdate):
        m_previous(clock::now()),
        m_lag(Duration::zero()),
        m_timePerUpdate(timePerUpdate){
}

