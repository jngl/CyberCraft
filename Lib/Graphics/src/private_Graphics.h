//
// Created by jngl on 10/07/2021.
//

#ifndef CYBERCRAFT_PRIVATE_GRAPHICS_H
#define CYBERCRAFT_PRIVATE_GRAPHICS_H

#include "Graphics/Graphics.h"

#include "SdlWindowAdapter.h"
#include "BgfxAdapter.h"

#include <CyberBase/Math.h>
#include <CyberBase/Bases.h>
#include <CyberBase/pointer.h>

#include <Ports/Texture.h>

#include <Ports/Key.h>
#include <Ports/GpuProgram.h>

#include <exception>
#include <string>
#include <filesystem>

#include <SDL_keycode.h>

struct SDL_Window;

namespace cg::Impl {
    class GraphicsAdapter : public cp::Ports
    {
    public:
        GraphicsAdapter();

        cp::GpuAdapter& getGpuAdapter() override;
        cp::Window& getWindow() override;

    private:
        SdlWindowAdapter m_window;
        std::unique_ptr<cp::GpuAdapter> m_bgfxAdapter;
    };
}

#endif //CYBERCRAFT_PRIVATE_GRAPHICS_H
