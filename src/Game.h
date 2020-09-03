//
// Created by jngl on 18/08/2020.
//

#ifndef CYBERCRAFT_GAME_H
#define CYBERCRAFT_GAME_H

#include <Core/Window.h>

#include "Game/Component.h"
#include "Game/Bloc.h"
#include "Game/World.h"

struct Player {
    component::Sprite sprite;
    component::Player player;
    math::Vector2f pos;
};

class Game {
public:
    explicit Game(GraphicsContext& graphicsContext);

    void update();
    void draw();

private:

    Player player{
            component::Sprite {
                    math::Vector2i {24,0},
                    Color{255,192,0},
                    Color{0,0,0,0}
            },
            component::Player{0},
            math::Vector2f {3,5}
    };

    World world;
    TextureHandle texture;
    GraphicsContext& m_graphicsContext;
};


#endif //CYBERCRAFT_GAME_H
