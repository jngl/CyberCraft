//
// Created by jngl on 08/05/2021.
//

#include "Game.h"

#include <Ports.h>

Game::Game(cp::Ports& ports):
m_ports(ports),
m_renderer2d(m_ports.getGpuAdapter()),
m_textureTest(m_ports.getGpuAdapter().getTextureFactory().loadTextureFromFile("dirt")){
}

void Game::update() {
    static constexpr float speed = 0.1f;

    cp::Window& window = m_ports.getWindow();

    if(window.isKeyPressed(cp::Key::UP)){
        m_pos.y -= speed;
    }

    if(window.isKeyPressed(cp::Key::DOWN)){
        m_pos.y += speed;
    }

    if(window.isKeyPressed(cp::Key::LEFT)){
        m_pos.x -= speed;
    }

    if(window.isKeyPressed(cp::Key::RIGHT)){
        m_pos.x += speed;
    }
}

void Game::draw() {
    auto size = m_ports.getWindow().getSize();
    m_renderer2d.updateSize(size);

    m_renderer2d.drawSprite(cc::Vector2f{400, 400}, cc::Vector2f{200, 200}, *m_textureTest);

    m_renderer2d.drawRectangle(m_pos, cc::Vector2f{m_playerSize, m_playerSize}, cc::Color{0,255,0});



}

extern "C" ck::Game* createGame(cp::Ports* ports){
    return new Game(*ports);
}
