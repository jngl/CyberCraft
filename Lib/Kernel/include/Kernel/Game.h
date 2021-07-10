//
// Created by jngl on 19/09/2020.
//

#ifndef CYBERCRAFT_GAME_H
#define CYBERCRAFT_GAME_H

#include <Core/Bases.h>

<<<<<<< HEAD:Lib/Kernel/include/Kernel/Game.h
namespace ck {
=======
namespace cc {
>>>>>>> b0d8808aab9721dbaa8c9afaf9c8a706f1faee8f:LibCyberCraftCore/include/Core/Game.h
    class Game: public cc::NonCopyable {
    public:
        virtual void update() = 0;
        virtual void draw() = 0;
    };
}

#endif //CYBERCRAFT_GAME_H
