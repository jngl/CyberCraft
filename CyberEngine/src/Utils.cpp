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

ck::Key keyFromSdlKey(SDL_Keycode sdlKey){
    switch (sdlKey){
        case SDLK_ESCAPE:
            return ck::Key::ESCAPE;
        case SDLK_UP:
            return ck::Key::UP;
        case SDLK_DOWN:
            return ck::Key::DOWN;
        case SDLK_LEFT:
            return ck::Key::LEFT;
        case SDLK_RIGHT:
            return ck::Key::RIGHT;
        case SDLK_F1:
            return ck::Key::F1;
        case SDLK_F2:
            return ck::Key::F2;
        case SDLK_F3:
            return ck::Key::F3;
        case SDLK_F4:
            return ck::Key::F4;
        case SDLK_F5:
            return ck::Key::F5;
        case SDLK_F6:
            return ck::Key::F6;
        case SDLK_F7:
            return ck::Key::F7;
        case SDLK_F8:
            return ck::Key::F8;
        case SDLK_F9:
            return ck::Key::F9;
        case SDLK_F10:
            return ck::Key::F10;
        case SDLK_F11:
            return ck::Key::F11;
        case SDLK_F12:
            return ck::Key::F12;
        default:
            return ck::Key::UNKNOWN;
    }
}