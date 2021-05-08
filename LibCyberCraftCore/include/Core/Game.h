//
// Created by jngl on 19/09/2020.
//

#ifndef CYBERCRAFT_GAME_H
#define CYBERCRAFT_GAME_H

#include <Core/Bases.h>

namespace cc {
    class Game: public cc::NonCopyable {
    public:
        virtual void update() = 0;
        virtual void draw() = 0;
    };
}

#endif //CYBERCRAFT_GAME_H
