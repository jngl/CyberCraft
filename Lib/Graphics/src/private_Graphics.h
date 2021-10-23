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

#include <exception>
#include <string>
#include <filesystem>

#include <SDL_keycode.h>

struct SDL_Window;

namespace cg::Impl {

    class Renderer2d : public cc::NonCopyable, public ck::ColoredRectangleDrawer {
    public:
        explicit Renderer2d(BgfxProgram& shader);
        ~Renderer2d() override;

        void updateSize(cc::Vector2ui size);

        void drawRectangle(const cc::Vector2f& pos, const cc::Vector2f& size, const cc::Color& color) override;

    private:
        bgfx::VertexBufferHandle m_rectangleVertices{};
        bgfx::IndexBufferHandle m_rectangleIndices{};
        BgfxProgram& m_program;
        BgfxUniform m_color;

        void setViewTransform(const cc::Matrix4f& proj, const cc::Matrix4f& view);
    };

    class Common
    {
    public:
        Common();

        void startFrame();
        void endFrame();

        Renderer2d& getRenderer2d();

        void processEvent(ck::ExitListener& exitListener, ck::KeyListener& keyListener);

    private:
        SdlWindowAdapter m_window;
        BgfxAdapter m_bgfxAdapter;
        BgfxTextureFactory m_textures;
        BgfxProgramFactory m_programs;
        Renderer2d m_renderer2d;
    };

    class GraphicsImpl {
    public:
        GraphicsImpl();

        void processEvent(ck::ExitListener& exitListener, ck::KeyListener& keyListener);

        std::unique_ptr<Frame> createFrame();
    private:
        Common m_common;
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
}

#endif //CYBERCRAFT_PRIVATE_GRAPHICS_H
