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

#include <Kernel/Engine.h>
#include <Kernel/Key.h>
#include <Kernel/Texture.h>

#include <exception>
#include <string>
#include <filesystem>

#include <bgfx/bgfx.h>

#include <SDL_keycode.h>

struct SDL_Window;

namespace cg::Impl {
    class TextureManager : public ck::TextureManager{
    public:
        TextureManager(BgfxAdapter&);

        [[nodiscard]] ck::TextureHandle getHandleFromFile(std::string_view filename) override;

        void loadTexture(ck::TextureHandle) override;
        void unloadTexture(ck::TextureHandle) override;

    private:
        struct Texture{
            std::filesystem::path file;
            BgfxTexture texture;
        };

        std::vector<Texture> m_textures;
        BgfxAdapter& m_bgfxAdapter;

        void loadTexture(const std::filesystem::path& file);
    };

    class ShaderManager {
    public:
        explicit ShaderManager(BgfxAdapter&);

        [[nodiscard]] ProgramHandle getHandleFromFile(std::string_view filename);

        [[nodiscard]] std::string getShaderDir() const;

    private:
        struct Shader{
            std::string name;
            ProgramHandle m_program;
        };

        BgfxAdapter& m_bgfxAdapter;
        std::vector<Shader> m_shaders;

        static std::optional<std::string> fileStemToShaderName(std::string_view fileStem);

        ShaderHandle loadShader(std::string_view name);
        void loadShaderProgram(std::string_view name);
    };

    class Renderer2d : public cc::NonCopyable, public ck::ColoredRectangleDrawer {
    public:
        Renderer2d();
        ~Renderer2d() override;

        void setShader(ProgramHandle shader);

        void updateSize(cc::Vector2ui size);

        void drawRectangle(const cc::Vector2f& pos, const cc::Vector2f& size, const cc::Color& color) override;

    private:
        bgfx::VertexBufferHandle m_rectangleVertices{};
        bgfx::IndexBufferHandle m_rectangleIndices{};
        ProgramHandle m_program{};
        bgfx::UniformHandle m_color{};

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
        TextureManager m_textures;
        ShaderManager m_shaders;
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

        explicit Frame(Common&) ;
        ~Frame() override;

        ck::ColoredRectangleDrawer& getColoredRectangleDrawer() override;

    private:
        Common& m_common;
    };
}

#endif //CYBERCRAFT_PRIVATE_GRAPHICS_H
