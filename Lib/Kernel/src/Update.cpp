//
// Created by jngl on 18/07/2020.
//

#include "Kernel/Update.h"

<<<<<<< HEAD:Lib/Kernel/src/Update.cpp
namespace ck {
=======
namespace cc {
>>>>>>> b0d8808aab9721dbaa8c9afaf9c8a706f1faee8f:LibCyberCraftCore/src/Core/Update.cpp
    FixStepUpdater::FixStepUpdater(const Duration &timePerUpdate) :
            m_previous(clock::now()),
            m_lag(Duration::zero()),
            m_timePerUpdate(timePerUpdate) {
    }
}

