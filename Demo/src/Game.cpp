//
// Created by jngl on 08/05/2021.
//

#include "Game.h"

enum class Direction{
    UP,
    DOWN,
    LEFT,
    RIGHT
};

template<Direction dir>
class CommandMove : public ck::Command, public cc::NonCopyable

{
public:
    explicit CommandMove(cc::Vector2f& pos):
    m_pos(pos)
    {}

    static constexpr float speed = 0.1f;

    void exec() override {
        if constexpr(dir == Direction::UP) {
            m_pos.y -= speed;
        } else if constexpr(dir == Direction::DOWN) {
            m_pos.y += speed;
        } else if constexpr(dir == Direction::LEFT) {
            m_pos.x -= speed;
        } else if constexpr(dir == Direction::RIGHT) {
            m_pos.x += speed;
        }
    }

private:
    cc::Vector2f& m_pos;
};

class CommandExit : public ck::Command
{
public:
    explicit CommandExit(ck::Runnable& runnable):

    m_runnable(runnable)
    {}

    void exec() override {
        m_runnable.exit();
    }

private:
    ck::Runnable& m_runnable;
};

Game::Game() {
    createOneFrameAction(std::make_unique<CommandExit>(*this), ck::Key::ESCAPE);

    createMultiFrameAction(std::make_unique<CommandMove<Direction::UP>>(m_pos), ck::Key::UP);
    createMultiFrameAction(std::make_unique<CommandMove<Direction::DOWN>>(m_pos), ck::Key::DOWN);
    createMultiFrameAction(std::make_unique<CommandMove<Direction::LEFT>>(m_pos), ck::Key::LEFT);
    createMultiFrameAction(std::make_unique<CommandMove<Direction::RIGHT>>(m_pos), ck::Key::RIGHT);
}

void Game::render(ck::ColoredRectangleDrawer &renderer) {
    renderer.drawRectangle(m_pos, cc::Vector2f{m_playerSize, m_playerSize}, cc::Color{255,255,255});
}

extern "C" ck::GameBase* createGame(){
    return new Game();
}