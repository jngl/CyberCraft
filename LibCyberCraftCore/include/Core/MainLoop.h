//
// Created by jngl on 19/09/2020.
//

#ifndef CYBERCRAFT_MAINLOOP_H
#define CYBERCRAFT_MAINLOOP_H

#include <Core/Common.h>

#include <chrono>

namespace cc {
    [[maybe_unused]] int mainLoop(Window &window, RenderContext &renderContext, Game &game, std::chrono::milliseconds updateTime);
}

#endif //CYBERCRAFT_MAINLOOP_H
