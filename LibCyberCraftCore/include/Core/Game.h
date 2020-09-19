//
// Created by jngl on 19/09/2020.
//

#ifndef CYBERCRAFT_GAME_H
#define CYBERCRAFT_GAME_H

namespace ccCore {
    class Game {
    public:
        virtual void update() = 0;

        virtual void draw() = 0;
    };
}

#endif //CYBERCRAFT_GAME_H
