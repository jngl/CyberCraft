//
// Created by jngl on 04/06/2021.
//

#ifndef CYBERCRAFT_WINDOWSDL_H
#define CYBERCRAFT_WINDOWSDL_H

#include <Core/Math.h>

#include <SDL2/SDL.h>

class WindowSdl {
public:
    WindowSdl();
    ~WindowSdl();

    SDL_Window* GetSdlWindow();

    void swap();

    void* sdlNativeWindowHandle();

    [[nodiscard]] cc::Vector2ui getSize() const;

private:
    SDL_Window *m_window;
};

#endif //CYBERCRAFT_WINDOWSDL_H
