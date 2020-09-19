//
// Created by jngl on 02/09/2020.
//

#ifndef CYBERCRAFT_GAMEENIGNE_H
#define CYBERCRAFT_GAMEENIGNE_H

#include <memory>

#include <Core/Common.h>
#include <Core/Error.h>
#include <Core/Update.h>

class GameEngine {
public:

    GameEngine(Window& window, RenderContext& renderContext, Game& game);

    int exec();

private:
    Window& m_window;
    RenderContext& m_renderContext;
    Game& m_game;
    FixStepUpdater m_updater;

    constexpr static std::chrono::milliseconds updateTime{33};
};




#endif //CYBERCRAFT_GAMEENIGNE_H
