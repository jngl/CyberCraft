//
// Created by jngl on 27/06/2020.
//

#ifndef LIB_CYBERCRAFT_COMMON_H
#define LIB_CYBERCRAFT_COMMON_H

#include <string_view>

namespace sf{
    //Vector
    template<class T>
    class Vector2;

    using Vector2f = Vector2<float>;

    //Rect
    template<class T>
    class Rect;

    using IntRect = Rect<int>;

    //Graphics
    class View;
    class Texture;
    class Sprite;
    class RenderTarget;
    class RenderWindow;
}

class Window;

void printTabs(int nb);

using Uint32 = unsigned int;
static_assert(sizeof(Uint32) == 4, "size of Uint32 must be 32 bite");

#endif //LIB_CYBERCRAFT_COMMON_H
