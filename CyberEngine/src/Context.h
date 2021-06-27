//
// Created by jngl on 05/06/2021.
//

#ifndef CYBERCRAFT_CONTEXT_H
#define CYBERCRAFT_CONTEXT_H

#include <Core/Math.h>
#include "Utils.h"

#include <memory>

class Frame;
class WindowSdl;

class Context{
public:
    explicit Context(WindowSdl& win);

    void beginFrame(cc::Vector2ui newSize);
    void endFrame();

    [[nodiscard]] GraphicsApi getApi() const;

private:
    cc::Vector2ui m_size;

    bool sdlSetWindow(WindowSdl& win);
};


#endif //CYBERCRAFT_CONTEXT_H
