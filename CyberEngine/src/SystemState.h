//
// Created by jngl on 05/06/2021.
//

#ifndef CYBERCRAFT_SYSTEMSTATE_H
#define CYBERCRAFT_SYSTEMSTATE_H

#include <Graphics/Graphics.h>
#include "GameLoader.h"

class SystemState{
public:
    SystemState();

    [[nodiscard]] bool isRunning() const;

    void frame();

private:
    cg::Graphics m_graphics;
    GameLoader m_gameLoader;
};

#endif //CYBERCRAFT_SYSTEMSTATE_H
