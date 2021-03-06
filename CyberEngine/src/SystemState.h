//
// Created by jngl on 05/06/2021.
//

#ifndef CYBERCRAFT_SYSTEMSTATE_H
#define CYBERCRAFT_SYSTEMSTATE_H

#include <Core/Bases.h>

#include <Graphics/Graphics.h>
#include "GameLoader.h"

#include <SDL.h>

class SystemState : public ck::KeyListener, public ck::ExitListener, public cc::NonCopyable{
public:
    [[nodiscard]] bool isRunning() const;

    void frame();

    void onKeyUp(ck::Key key) override;
    void onKeyDown(ck::Key key) override;

    void onExit() override;

private:
    cg::Graphics m_graphics;
    GameLoader m_gameLoader;
};

#endif //CYBERCRAFT_SYSTEMSTATE_H
