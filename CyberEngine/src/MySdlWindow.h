//
// Created by jngl on 04/06/2021.
//

#ifndef CYBERCRAFT_MYSDLWINDOW_H
#define CYBERCRAFT_MYSDLWINDOW_H

#include <Core/Math.h>

#include <SDL2/SDL.h>

class MySdlWindow {
public:
    MySdlWindow();
    ~MySdlWindow();

    SDL_Window* GetSdlWindow();

    void swap();

    void* sdlNativeWindowHandle();

    [[nodiscard]] cc::Vector2ui getSize() const;

private:
    SDL_Window *m_window;
};

#endif //CYBERCRAFT_MYSDLWINDOW_H
