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

class SystemState : public cc::NonCopyable{
public:
    SystemState();

    [[nodiscard]] bool isRunning() const;

    void frame();

//    void onKeyUp(cp::Key key) override;
//    void onKeyDown(cp::Key key) override;

private:
    std::unique_ptr<cp::GraphicsAdapter> m_graphicsAdapter;
    ck::Renderer2d m_renderer2d;
    GameLoader m_gameLoader;
};

#endif //CYBERCRAFT_SYSTEMSTATE_H
