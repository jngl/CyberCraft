//
// Created by jngl on 18/07/2020.
//

#ifndef CYBERCRAFT_COMPONENT_H
#define CYBERCRAFT_COMPONENT_H

#include <Core/Math.h>
#include <Core/Color.h>

namespace component{
    struct Sprite{
        ccCore::Vector2i textureIndex;
        ccCore::Color color;
        ccCore::Color backgroundColor;
        float rotation = 0; // in degree
    };
    struct Player{
        int timerMove;
    };
}


#endif //CYBERCRAFT_COMPONENT_H
