//
// Created by jngl on 18/07/2020.
//

#ifndef CYBERCRAFT_COMPONENT_H
#define CYBERCRAFT_COMPONENT_H

#include <Core/Math.h>
#include <Core/Color.h>

namespace component{
    struct Sprite{
        math::Vector2i textureIndex;
        Color color;
        Color backgroundColor;
    };
    struct Player{
        int timerMove;
    };
}


#endif //CYBERCRAFT_COMPONENT_H
