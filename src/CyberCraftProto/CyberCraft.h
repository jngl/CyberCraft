//
// Created by jngl on 18/08/2020.
//

#ifndef CYBERCRAFT_CYBERCRAFT_H
#define CYBERCRAFT_CYBERCRAFT_H

#include <Kernel/Engine2D.h>
#include <Kernel/Game.h>
#include <Core/pointer.h>

#include "Game/Component.h"
#include "Game/Bloc.h"
#include "Game/World.h"

struct Player {
    component::Sprite sprite;
    cc::Vector2f pos;
};

class CyberCraft : public ck::Game {
public:
    explicit CyberCraft(cc::Ref<ck::RenderContext2D> renderContext);
    CyberCraft(const CyberCraft&) = delete;
    CyberCraft(const CyberCraft&&) = delete;

    CyberCraft& operator=(const CyberCraft&) = delete;
    CyberCraft& operator=(CyberCraft&&) = delete;

    ~CyberCraft() override;

    void update() override;
    void draw() override;

private:

    Player player{
            component::Sprite {
                    cc::Vector2i {0,0},
                    cc::Color{255,192,0}, // NOLINT(cppcoreguidelines-avoid-magic-numbers,readability-magic-numbers)
                    cc::Color{0,0,0,0}
            },
            cc::Vector2f {3,5} // NOLINT(cppcoreguidelines-avoid-magic-numbers,readability-magic-numbers)
    };

    World m_world;
    ck::TextureHandle texture;
    cc::Ref<ck::RenderContext2D> m_renderContext;
};


#endif //CYBERCRAFT_CYBERCRAFT_H
