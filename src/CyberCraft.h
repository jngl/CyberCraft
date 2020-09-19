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

struct Player {
    component::Sprite sprite;
    component::Player player;
    ccCore::Vector2f pos;
};

class CyberCraft : public ccCore::Game {
public:
    explicit CyberCraft(ccCore::RenderContext& renderContext);

    void update() override;
    void draw() override;

private:

    Player player{
            component::Sprite {
                    ccCore::Vector2i {0,0},
                    ccCore::Color{255,192,0},
                    ccCore::Color{0,0,0,0}
            },
            component::Player{0},
            ccCore::Vector2f {3,5}
    };

    World m_world;
    ccCore::TextureHandle texture;
    ccCore::RenderContext& m_renderContext;
};


#endif //CYBERCRAFT_CYBERCRAFT_H
