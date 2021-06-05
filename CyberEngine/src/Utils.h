//
// Created by jngl on 04/06/2021.
//

#ifndef CYBERCRAFT_UTILS_H
#define CYBERCRAFT_UTILS_H

#include <Core/Math.h>
#include <Core/Key.h>

#include <exception>
#include <string>
#include <SDL_keycode.h>

constexpr int windowSizeXDefault = 1024;
constexpr int windowSizeYDefault = 768;

constexpr cc::Vector2f generateWindowViewSize(int windowX, int windowY){
    constexpr float minSize = 100;

    if(windowX > windowY){
        return {
                minSize * static_cast<float>(windowX)  / static_cast<float>(windowY),
                minSize
        };
    }

    return {
            minSize,
            minSize * static_cast<float>(windowY) / static_cast<float>(windowX)
    };
}

class SystemError : public std::exception
{
public:
    SystemError(std::string_view msg);
    [[nodiscard]] const char* what() const noexcept override;
private:
    std::string m_message;
};

cc::Key keyFromSdlKey(SDL_Keycode sdlKey);

#endif //CYBERCRAFT_UTILS_H
