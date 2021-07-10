//
// Created by jngl on 08/05/2021.
//

#ifndef CYBERCRAFT_GAME_H
#define CYBERCRAFT_GAME_H

<<<<<<< HEAD
#include <Kernel/Engine.h>

#include <Core/Bases.h>
#include <Core/Math.h>

class Game final : public ck::GameBase, public cc::NonCopyable {
public:
    Game();

    void render(ck::ColoredRectangleDrawer& renderer) final;

private:
    cc::Vector2f m_pos{200, 200};

    static constexpr float m_playerSize = 10;
=======
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
>>>>>>> b0d8808aab9721dbaa8c9afaf9c8a706f1faee8f
};

#endif //CYBERCRAFT_GAME_H
