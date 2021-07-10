//
// Created by jngl on 27/06/2020.
//

#ifndef LIB_CYBERCRAFT_COMMON_H
#define LIB_CYBERCRAFT_COMMON_H

#include <string_view>

namespace cc {
<<<<<<< HEAD:Lib/Core/include/Core/Common.h
=======
    struct Color;
    class Window;
    class RenderContext2D;
    class Game;

>>>>>>> b0d8808aab9721dbaa8c9afaf9c8a706f1faee8f:LibCyberCraftCore/include/Core/Common.h
    void printTabs(int nb);

    using Uint8 = unsigned char;
    using Uint32 = unsigned int;

    static_assert(sizeof(Uint8) == 1, "size of Uint8 must be 8 bite");
    static_assert(sizeof(Uint32) == 4, "size of Uint32 must be 32 bite");
}

#endif //LIB_CYBERCRAFT_COMMON_H
