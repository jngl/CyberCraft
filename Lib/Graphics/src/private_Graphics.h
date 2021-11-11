//
// Created by jngl on 10/07/2021.
//

#ifndef CYBERCRAFT_PRIVATE_GRAPHICS_H
#define CYBERCRAFT_PRIVATE_GRAPHICS_H

#include "Graphics/Graphics.h"

#include "SdlWindowAdapter.h"
#include "BgfxAdapter.h"

#include <Core/Math.h>
#include <Core/Bases.h>
#include <Core/pointer.h>

#include <Ports/Texture.h>

#include <Kernel/Engine.h>
#include <Kernel/Key.h>
#include <Kernel/GpuProgram.h>
#include <Kernel/Renderer2d.h>

#include <exception>
#include <string>
#include <filesystem>

#include <SDL_keycode.h>

struct SDL_Window;

namespace cg::Impl {
    class GraphicsAdapter : public ck::GraphicsAdapter
    {
    public:
        GraphicsAdapter();

        ck::GpuAdapter& getGpuAdapter() override;
        ck::Window& getWindow() override;

    private:
        SdlWindowAdapter m_window;
        std::unique_ptr<ck::GpuAdapter> m_bgfxAdapter;
    };
}

#endif //CYBERCRAFT_PRIVATE_GRAPHICS_H
