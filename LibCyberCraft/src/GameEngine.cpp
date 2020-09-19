//
// Created by jngl on 02/09/2020.
//

#include "GameEngine.h"

#include <Core/Game.h>
#include <Core/Window.h>
#include <Core/RenderContext.h>

GameEngine::GameEngine(Window& window, RenderContext& renderContext, Game& game):
m_window(window),
m_renderContext(renderContext),
m_game(game),
m_updater(updateTime)
{
}

int GameEngine::exec() {
    while (m_window.isOpen()) {
        m_window.beginFrame();

        m_game.draw();

        m_updater.update([this](){
            m_game.update();
        });

        m_window.endFrame();
    }
    return 0;
}



