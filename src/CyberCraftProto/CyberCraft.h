//
// Created by jngl on 18/08/2020.
//

#ifndef CYBERCRAFT_CYBERCRAFT_H
#define CYBERCRAFT_CYBERCRAFT_H

#include <Core/RenderContext.h>
#include <Core/Game.h>
#include <Core/pointer.h>

#include "Game/Component.h"
#include "Game/Bloc.h"
#include "Game/World.h"

struct Player {
    component::Sprite sprite;
    cc::Vector2f pos;
};

class CyberCraft : public cc::Game {
public:
    explicit CyberCraft(cc::Ref<cc::RenderContext> renderContext);

    void update() override;
    void draw() override;

private:

    Player player{
            component::Sprite {
                    cc::Vector2i {0,0},
                    cc::Color{255,192,0},
                    cc::Color{0,0,0,0}
            },
            cc::Vector2f {3,5}
    };

    World m_world;
    cc::TextureHandle texture;
    cc::Ref<cc::RenderContext> m_renderContext;
};


#endif //CYBERCRAFT_CYBERCRAFT_H
