//
// Created by jngl on 05/06/2021.
//

#ifndef CYBERCRAFT_SYSTEMSTATE_H
#define CYBERCRAFT_SYSTEMSTATE_H

#include <Core/Bases.h>


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
    std::unique_ptr<cp::Ports> m_graphicsAdapter;
    GameLoader m_gameLoader;
};

#endif //CYBERCRAFT_SYSTEMSTATE_H
