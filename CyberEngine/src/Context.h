//
// Created by jngl on 05/06/2021.
//

#ifndef CYBERCRAFT_CONTEXT_H
#define CYBERCRAFT_CONTEXT_H

#include <Core/Math.h>
#include "Renderer2d.h"
#include "Frame.h"
#include "Utils.h"

#include <memory>

class Frame;
class WindowSdl;

class Context{
public:
    explicit Context(WindowSdl& win);

    Frame beginFrame();

    [[nodiscard]] GraphicsApi getApi() const;

private:
    WindowSdl& m_window;
    cc::Vector2ui m_size;
    std::unique_ptr<Renderer2d> m_renderer2d;

    bool sdlSetWindow(WindowSdl& win);
};


#endif //CYBERCRAFT_CONTEXT_H
