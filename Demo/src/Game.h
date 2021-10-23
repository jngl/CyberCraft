//
// Created by jngl on 08/05/2021.
//

#ifndef CYBERCRAFT_GAME_H
#define CYBERCRAFT_GAME_H

#include <Kernel/Engine.h>

#include <Core/Bases.h>
#include <Core/Math.h>

class Game final : public ck::GameBase, public cc::NonCopyable {
public:
    Game();

    void render(ck::ColoredRectangleDrawer& renderer) final;

private:
    cc::Vector2f m_pos{200, 200};

    static constexpr float m_playerSize = 50;
};

#endif //CYBERCRAFT_GAME_H
