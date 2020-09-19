//
// Created by jngl on 18/08/2020.
//

#ifndef CYBERCRAFT_CYBERCRAFT_H
#define CYBERCRAFT_CYBERCRAFT_H

#include <Core/RenderContext.h>
#include <Core/Game.h>

#include "Game/Component.h"
#include "Game/Bloc.h"
#include "Game/World.h"

class RenderContext;

struct Player {
    component::Sprite sprite;
    component::Player player;
    math::Vector2f pos;
};

class CyberCraft : public Game {
public:
    explicit CyberCraft(RenderContext& renderContext);

    void update() override;
    void draw() override;

private:

    Player player{
            component::Sprite {
                    math::Vector2i {0,0},
                    Color{255,192,0},
                    Color{0,0,0,0}
            },
            component::Player{0},
            math::Vector2f {3,5}
    };

    World world;
    TextureHandle texture;
    RenderContext& m_renderContext;
};


#endif //CYBERCRAFT_CYBERCRAFT_H
