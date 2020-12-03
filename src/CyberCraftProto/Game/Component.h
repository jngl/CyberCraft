//
// Created by jngl on 18/07/2020.
//

#ifndef CYBERCRAFT_COMPONENT_H
#define CYBERCRAFT_COMPONENT_H

#include <Core/Math.h>
#include <Core/Color.h>

namespace component{
    struct Sprite{
        cc::Vector2i textureIndex;
        cc::Color color;
        cc::Color backgroundColor;
        float rotation = 0; // in degree
    };
}


#endif //CYBERCRAFT_COMPONENT_H
