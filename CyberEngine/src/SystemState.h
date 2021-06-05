//
// Created by jngl on 05/06/2021.
//

#ifndef CYBERCRAFT_SYSTEMSTATE_H
#define CYBERCRAFT_SYSTEMSTATE_H

#include "TextureManager.h"
#include "BgfxFrame.h"
#include "MySdlWindow.h"
#include "MyBgfxContext.h"
#include "GameLoader.h"

class SystemState{
public:
    SystemState();

    [[nodiscard]] bool isRunning() const;

    void frame();

private:
    MySdlWindow m_window;
    MyBgfxContext m_context;
    TextureManager m_textures;
    GameLoader m_gameLoader;
};

#endif //CYBERCRAFT_SYSTEMSTATE_H
