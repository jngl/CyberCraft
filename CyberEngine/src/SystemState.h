//
// Created by jngl on 05/06/2021.
//

#ifndef CYBERCRAFT_SYSTEMSTATE_H
#define CYBERCRAFT_SYSTEMSTATE_H

#include <Core/Bases.h>

#include <Kernel/Renderer2d.h>

#include <Graphics/Graphics.h>
#include "GameLoader.h"

#include <SDL.h>

class SystemState : public ck::KeyListener, public ck::ExitListener, public cc::NonCopyable{
public:
    SystemState();

    [[nodiscard]] bool isRunning() const;

    void frame();

    void onKeyUp(ck::Key key) override;
    void onKeyDown(ck::Key key) override;

    void onExit() override;

private:
    std::unique_ptr<ck::GraphicsAdapter> m_graphicsAdapter;
    GameLoader m_gameLoader;
    ck::Renderer2d m_renderer2d;
};

#endif //CYBERCRAFT_SYSTEMSTATE_H
