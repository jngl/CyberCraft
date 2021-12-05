//
// Created by jngl on 08/05/2021.
//

#ifndef CYBERCRAFT_GAME_H
#define CYBERCRAFT_GAME_H

#include <Kernel/Game.h>
#include <Kernel/Renderer2d.h>

#include <Core/Bases.h>
#include <Core/Math.h>
#include "Game.h"

namespace cp
{
    class Ports;
}

class Game final : public ck::Game {
public:
    Game(cp::Ports& ports);

    void update() final;
    void draw() final;

private:
    cp::Ports& m_ports;
    ck::Renderer2d m_renderer2d;
    cc::Vector2f m_pos{20, 20};
    std::shared_ptr<cp::Texture> m_textureTest;

    static constexpr float m_playerSize = 50;
};

#endif //CYBERCRAFT_GAME_H
