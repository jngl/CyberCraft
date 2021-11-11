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

#include <Kernel/Engine.h>
#include <Kernel/Key.h>
#include <Kernel/Texture.h>
#include <Kernel/GpuProgram.h>
#include <Kernel/Renderer2d.h>

#include <exception>
#include <string>
#include <filesystem>

#include <SDL_keycode.h>

struct SDL_Window;

namespace cg::Impl {
    class Common
    {
    public:
        Common();

        SdlWindowAdapter m_window;
        std::unique_ptr<ck::GpuAdapter> m_bgfxAdapter;
        ck::Renderer2d m_renderer2d;
    };

    class Frame : public ck::Frame
    {
    public:
        friend class Graphics;

        explicit Frame(Common&);
        Frame(const Frame&) = delete;
        Frame(Frame&&) noexcept;

        Frame& operator=(const Frame&) = delete;
        Frame& operator=(Frame&&) noexcept;

        ~Frame() override;

        ck::ColoredRectangleDrawer& getColoredRectangleDrawer() override;

    private:
        Common* m_common;
    };

    class GraphicsAdapter : public ck::GraphicsAdapter
    {
    public:
        std::unique_ptr<ck::Frame> createFrame() override;
        void processEvent(ck::ExitListener& exitListener, ck::KeyListener& keyListener) override;

    private:
        Common m_common;
    };
}

#endif //CYBERCRAFT_PRIVATE_GRAPHICS_H
