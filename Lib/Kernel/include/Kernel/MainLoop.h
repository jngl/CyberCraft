//
// Created by jngl on 19/09/2020.
//

#ifndef CYBERCRAFT_MAINLOOP_H
#define CYBERCRAFT_MAINLOOP_H

#include <CyberBase/Common.h>

#include <chrono>

namespace cp
{
    class Window;
}

namespace ck {
    class RenderContext2D;
    class Game;

    [[maybe_unused]] int mainLoop(cp::Window &window, RenderContext2D &renderContext, Game &game, std::chrono::milliseconds updateTime);
}

#endif //CYBERCRAFT_MAINLOOP_H
