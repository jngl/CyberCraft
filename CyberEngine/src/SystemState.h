//
// Created by jngl on 05/06/2021.
//

#ifndef CYBERCRAFT_SYSTEMSTATE_H
#define CYBERCRAFT_SYSTEMSTATE_H

#include "TextureManager.h"
#include "ShaderManager.h"
#include "Frame.h"
#include "WindowSdl.h"
#include "Context.h"
#include "GameLoader.h"

class SystemState{
public:
    SystemState();

    [[nodiscard]] bool isRunning() const;

    void frame();

private:
    WindowSdl m_window;
    Context m_context;
    TextureManager m_textures;
    ShaderManager m_shaders;
    GameLoader m_gameLoader;
};

#endif //CYBERCRAFT_SYSTEMSTATE_H
