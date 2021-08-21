//
// Created by jngl on 18/08/2020.
//

#ifndef CYBERCRAFT_CYBERCRAFT_H
#define CYBERCRAFT_CYBERCRAFT_H

#include <Kernel/Engine2D.h>
#include <Kernel/Game.h>
#include <Kernel/Window.h>

#include <Core/pointer.h>

#include "Component.h"
#include "Bloc.h"
#include "World.h"

struct Player {
    component::Sprite sprite;
    cc::Vector2f pos;
};

class CyberCraft : public ck::Game {
public:
    explicit CyberCraft(cc::Ref<ck::RenderContext2D> renderContext, cc::Ref<ck::Window> win);
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
    cc::Ref<ck::Window> m_window;
};


#endif //CYBERCRAFT_CYBERCRAFT_H
