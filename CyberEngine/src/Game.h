//
// Created by jngl on 08/05/2021.
//

#ifndef CYBERCRAFT_GAME_H
#define CYBERCRAFT_GAME_H

#include <Core/Engine.h>
#include <Core/Bases.h>
#include <Core/Math.h>

class Game final : public cc::GameBase, public cc::NonCopyable {
public:
    Game();

    void render(cc::ColoredRectangleDrawer& renderer) final;

private:
    cc::Vector2f m_pos{0, 0};

    static constexpr float m_playerSize = 5;
};

#endif //CYBERCRAFT_GAME_H
