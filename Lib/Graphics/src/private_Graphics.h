//
// Created by jngl on 10/07/2021.
//

#ifndef CYBERCRAFT_PRIVATE_GRAPHICS_H
#define CYBERCRAFT_PRIVATE_GRAPHICS_H

#include "Graphics/Graphics.h"

#include <Core/Math.h>
#include <Core/Bases.h>

#include <Kernel/Engine.h>
#include <Kernel/Key.h>
#include <Kernel/Texture.h>
#include <Kernel/Shader.h>

#include <exception>
#include <string>
#include <filesystem>

#include <bgfx/bgfx.h>

#include <SDL_keycode.h>

class SDL_Window;

namespace cg::Impl {
    constexpr int windowSizeXDefault = 1024;
    constexpr int windowSizeYDefault = 768;

    constexpr cc::Vector2f generateWindowViewSize(int windowX, int windowY);

    constexpr ck::Key keyFromSdlKey(SDL_Keycode sdlKey);

    enum class GraphicsApi{
        Noop,         /// No rendering.
        Direct3D9,    /// Direct3D 9.0
        Direct3D11,   /// Direct3D 11.0
        Direct3D12,   /// Direct3D 12.0
        Gnm,          /// GNM
        Metal,        /// Metal
        Nvn,          /// NVN
        OpenGLES,     /// OpenGL ES 2.0+
        OpenGL,       /// OpenGL 2.1+
        Vulkan,       /// Vulkan
        WebGPU,       /// WebGPU
    };

    constexpr std::string_view GetGraphicsApiName(GraphicsApi api);
    constexpr std::string_view GetGraphicsApiShaderType(GraphicsApi api);

    class WindowSdl {
    public:
        WindowSdl();
        ~WindowSdl();

        SDL_Window* GetSdlWindow();

        void swap();

        void* sdlNativeWindowHandle();

        [[nodiscard]] cc::Vector2ui getSize() const;

    private:
        SDL_Window *m_window;
    };

    class Context{
    public:
        explicit Context(WindowSdl& win);

        void beginFrame(cc::Vector2ui newSize);
        void endFrame();

        [[nodiscard]] GraphicsApi getApi() const;

    private:
        cc::Vector2ui m_size;

        bool sdlSetWindow(WindowSdl& win);
    };

    class TextureManager : public ck::TextureManager {
    public:
        TextureManager();

        [[nodiscard]] ck::TextureHandle getHandleFromFile(std::string_view filename) override;
        void loadTexture(ck::TextureHandle handle) override;
        void unloadTexture(ck::TextureHandle handle) override;

    private:
        struct Texture{
            std::filesystem::path file;
        };

        std::vector<Texture> m_textures;

        void loadTexture(const std::filesystem::path& file);
    };

    class ShaderManager : public ck::ShaderManager {
    public:
        explicit ShaderManager(Context&);

        bgfx::ProgramHandle get(ck::ShaderHandle);

        [[nodiscard]] ck::ShaderHandle getHandleFromFile(std::string_view filename) override;
        void loadShader(ck::ShaderHandle handle) override;
        void unloadShader(ck::ShaderHandle handle) override;

        std::string getShaderDir() const;

    private:
        struct Shader{
            std::string name;
            bgfx::ProgramHandle m_program;
        };

        Context& m_context;
        std::vector<Shader> m_shaders;

        static std::optional<std::string> fileStemToShaderName(std::string_view fileStem);

        bgfx::ShaderHandle loadShader(std::string_view name);
        void loadShaderProgram(std::string_view name);
    };

    class Renderer2d : public cc::NonCopyable, public ck::ColoredRectangleDrawer {
    public:
        Renderer2d();
        ~Renderer2d() override;

        void setShader(bgfx::ProgramHandle shader);

        void updateSize(cc::Vector2ui size);

        void drawRectangle(const cc::Vector2f& pos, const cc::Vector2f& size, const cc::Color& color) override;

    private:
        bgfx::VertexBufferHandle m_rectangleVertices{};
        bgfx::IndexBufferHandle m_rectangleIndices{};
        bgfx::ProgramHandle m_program{};
        bgfx::UniformHandle m_color{};

        void setViewTransform(const cc::Matrix4f& proj, const cc::Matrix4f& view);
    };

    struct GraphicsData {
        WindowSdl m_window;
        Context m_context;
        TextureManager m_textures;
        ShaderManager m_shaders;
        Renderer2d m_renderer2d;

        GraphicsData();
    };

    class Frame : public ck::Frame
    {
    public:
        friend class Graphics;

        explicit Frame(Graphics&) ;
        ~Frame() override;

        ck::ColoredRectangleDrawer& getColoredRectangleDrawer() override;

    private:
        Graphics& m_graphics;
    };
}

#include "private_impl_Graphics.h"

#endif //CYBERCRAFT_PRIVATE_GRAPHICS_H
