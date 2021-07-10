//
// Created by jngl on 05/06/2021.
//

#ifndef CYBERCRAFT_SYSTEMSTATE_H
#define CYBERCRAFT_SYSTEMSTATE_H

#include "TextureManager.h"
<<<<<<< HEAD
#include "ShaderManager.h"
#include "WindowSdl.h"
#include "Context.h"
#include "GameLoader.h"
#include "Renderer2d.h"
=======
#include "BgfxFrame.h"
#include "MySdlWindow.h"
#include "MyBgfxContext.h"
#include "GameLoader.h"
>>>>>>> b0d8808aab9721dbaa8c9afaf9c8a706f1faee8f

class SystemState{
public:
    SystemState();

    [[nodiscard]] bool isRunning() const;

    void frame();

private:
<<<<<<< HEAD
    WindowSdl m_window;
    Context m_context;
    TextureManager m_textures;
    ShaderManager m_shaders;
    Renderer2d m_renderer2d;
=======
    MySdlWindow m_window;
    MyBgfxContext m_context;
    TextureManager m_textures;
>>>>>>> b0d8808aab9721dbaa8c9afaf9c8a706f1faee8f
    GameLoader m_gameLoader;
};

#endif //CYBERCRAFT_SYSTEMSTATE_H
