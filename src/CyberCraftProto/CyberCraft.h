//
// Created by jngl on 18/08/2020.
//

#ifndef CYBERCRAFT_CYBERCRAFT_H
#define CYBERCRAFT_CYBERCRAFT_H

<<<<<<< HEAD
#include <Kernel/Engine2D.h>
#include <Kernel/Game.h>
=======
#include <Core/Engine2D.h>
#include <Core/Game.h>
>>>>>>> b0d8808aab9721dbaa8c9afaf9c8a706f1faee8f
#include <Core/pointer.h>

#include "Game/Component.h"
#include "Game/Bloc.h"
#include "Game/World.h"

struct Player {
    component::Sprite sprite;
    cc::Vector2f pos;
};

<<<<<<< HEAD
class CyberCraft : public ck::Game {
public:
    explicit CyberCraft(cc::Ref<ck::RenderContext2D> renderContext);
=======
class CyberCraft : public cc::Game {
public:
    explicit CyberCraft(cc::Ref<cc::RenderContext2D> renderContext);
>>>>>>> b0d8808aab9721dbaa8c9afaf9c8a706f1faee8f
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
<<<<<<< HEAD
    ck::TextureHandle texture;
    cc::Ref<ck::RenderContext2D> m_renderContext;
=======
    cc::TextureHandle texture;
    cc::Ref<cc::RenderContext2D> m_renderContext;
>>>>>>> b0d8808aab9721dbaa8c9afaf9c8a706f1faee8f
};


#endif //CYBERCRAFT_CYBERCRAFT_H
