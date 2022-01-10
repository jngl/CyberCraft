//
// Created by jngl on 18/07/2020.
//

#ifndef CYBERCRAFT_COMPONENT_H
#define CYBERCRAFT_COMPONENT_H

#include <Core/Math.h>
#include <CyberBase/Color.hpp>

namespace component{
    struct Sprite{
        cc::Vector2i textureIndex;
        cb::Color color;
        cb::Color backgroundColor;
        float rotation = 0; // in degree
    };
}


#endif //CYBERCRAFT_COMPONENT_H
