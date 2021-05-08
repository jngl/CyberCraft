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
class CommandMove : public cc::Command, public cc::NonCopyable
{
public:
    explicit CommandMove(cc::Vector2f& pos):
    m_pos(pos)
    {}

    static constexpr float speed = 1.f;

    void exec() override {
        if constexpr(dir == Direction::UP) {
            m_pos.y += speed;
        } else if constexpr(dir == Direction::DOWN) {
            m_pos.y -= speed;
        } else if constexpr(dir == Direction::LEFT) {
            m_pos.x -= speed;
        } else if constexpr(dir == Direction::RIGHT) {
            m_pos.x += speed;
        }
    }

private:
    cc::Vector2f& m_pos;
};

class CommandExit : public cc::Command
{
public:
    explicit CommandExit(cc::Runnable& runnable):
    m_runnable(runnable)
    {}

    void exec() override {
        m_runnable.exit();
    }

private:
    cc::Runnable& m_runnable;
};

Game::Game() {
    createOneFrameAction(std::make_unique<CommandExit>(*this), cc::Key::ESCAPE);

    createMultiFrameAction(std::make_unique<CommandMove<Direction::UP>>(m_pos), cc::Key::UP);
    createMultiFrameAction(std::make_unique<CommandMove<Direction::DOWN>>(m_pos), cc::Key::DOWN);
    createMultiFrameAction(std::make_unique<CommandMove<Direction::LEFT>>(m_pos), cc::Key::LEFT);
    createMultiFrameAction(std::make_unique<CommandMove<Direction::RIGHT>>(m_pos), cc::Key::RIGHT);
}

void Game::render(cc::ColoredRectangleDrawer &renderer) {
    renderer.drawRectangle(m_pos, cc::Vector2f{m_playerSize, m_playerSize}, cc::Color{0,100,0});
}

extern "C" cc::GameBase* createGame(){
    return new Game();
}