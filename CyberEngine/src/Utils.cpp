//
// Created by jngl on 04/06/2021.
//

#include "Utils.h"

SystemError::SystemError(std::string_view msg)
{
    m_message = std::string("System Error : ") + std::string(msg);
}

[[nodiscard]] const char* SystemError::what() const noexcept{
    return m_message.c_str();
}

cc::Key keyFromSdlKey(SDL_Keycode sdlKey){
    switch (sdlKey){
        case SDLK_ESCAPE:
            return cc::Key::ESCAPE;
        case SDLK_UP:
            return cc::Key::UP;
        case SDLK_DOWN:
            return cc::Key::DOWN;
        case SDLK_LEFT:
            return cc::Key::LEFT;
        case SDLK_RIGHT:
            return cc::Key::RIGHT;
        case SDLK_F1:
            return cc::Key::F1;
        case SDLK_F2:
            return cc::Key::F2;
        case SDLK_F3:
            return cc::Key::F3;
        case SDLK_F4:
            return cc::Key::F4;
        case SDLK_F5:
            return cc::Key::F5;
        case SDLK_F6:
            return cc::Key::F6;
        case SDLK_F7:
            return cc::Key::F7;
        case SDLK_F8:
            return cc::Key::F8;
        case SDLK_F9:
            return cc::Key::F9;
        case SDLK_F10:
            return cc::Key::F10;
        case SDLK_F11:
            return cc::Key::F11;
        case SDLK_F12:
            return cc::Key::F12;
        default:
            return cc::Key::UNKNOWN;
    }
}