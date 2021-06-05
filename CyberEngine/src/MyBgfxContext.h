//
// Created by jngl on 05/06/2021.
//

#ifndef CYBERCRAFT_MYBGFXCONTEXT_H
#define CYBERCRAFT_MYBGFXCONTEXT_H

#include <Core/Math.h>

class BgfxFrame;
class MySdlWindow;

class MyBgfxContext{
public:
    explicit MyBgfxContext(MySdlWindow& win);

    BgfxFrame beginFrame();

private:
    MySdlWindow& m_window;
    cc::Vector2ui m_size;

    bool sdlSetWindow(MySdlWindow& win);
};


#endif //CYBERCRAFT_MYBGFXCONTEXT_H
