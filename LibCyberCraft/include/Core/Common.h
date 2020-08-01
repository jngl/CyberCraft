//
// Created by jngl on 27/06/2020.
//

#ifndef CYBERCRAFT_COMMON_H
#define CYBERCRAFT_COMMON_H

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

void printTabs(int nb);

#endif //CYBERCRAFT_COMMON_H