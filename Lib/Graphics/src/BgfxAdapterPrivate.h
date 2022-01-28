//
// Created by jngl on 11/11/2021.
//

#ifndef CYBERCRAFT_BGFXADAPTERPRIVATE_H
#define CYBERCRAFT_BGFXADAPTERPRIVATE_H

#include "BgfxAdapter.h"

#include <Ports/GpuProgram.h>
#include <Ports/GpuBuffer.h>
#include <Ports/Texture.h>

#include <bgfx/bgfx.h>

#include <CyberBase/Memory.h>
#include <CyberBase/Math.h>

#include <filesystem>
#include <vector>

#include "Enum.h"

namespace bgfx
{
    struct ProgramHandle;
}

namespace cg::Impl {
    class SdlWindowAdapter;
    class BgfxAdapter;
    class BgfxVertexLayout;
    class BgfxContext;

    ////////////////////////////////////////////////////////////////////////////////////////////////////////
    /// Index Buffer
    ///////////////////////////////////////////////////////////////////////////////////////////////////////
    class BgfxIndexBuffer : public cp::IndexBuffer{
    public:
        explicit BgfxIndexBuffer(const cc::ByteArrayView&);
        ~BgfxIndexBuffer() override;

        [[nodiscard]] bgfx::IndexBufferHandle getBgfxHandle() const;

    private:
        bgfx::IndexBufferHandle m_handle;
    };

    ////////////////////////////////////////////////////////////////////////////////////////////////////////
    /// Vertex Buffer
    ///////////////////////////////////////////////////////////////////////////////////////////////////////
    class BgfxVertexBuffer : public cp::VertexBuffer{
    public:
        BgfxVertexBuffer(const cc::ByteArrayView& data, const BgfxVertexLayout& layout);
        ~BgfxVertexBuffer() override;

        [[nodiscard]] bgfx::VertexBufferHandle getBgfxHandle() const;

    private:
        bgfx::VertexBufferHandle m_handle;
    };

    ////////////////////////////////////////////////////////////////////////////////////////////////////////
    /// Vertex Layout
    ///////////////////////////////////////////////////////////////////////////////////////////////////////
    class BgfxVertexLayout : public cp::VertexLayout{
    public:
        void begin() override;
        void add(cp::Attrib attrib, uint8_t num, cp::AttribType type, bool normalized = false, bool asInt = false) override;
        void end() override;

        [[nodiscard]] const bgfx::VertexLayout& getBgfxLayout() const;

    private:
        bgfx::VertexLayout m_layout;
    };

    ////////////////////////////////////////////////////////////////////////////////////////////////////////
    /// Vertex Layout
    ///////////////////////////////////////////////////////////////////////////////////////////////////////
    class bgfxGpuBufferFactory : public cp::GpuBufferFactory{
    public:
        std::unique_ptr<cp::IndexBuffer> createIndexBuffer(const cc::ByteArrayView& data) override;
        std::unique_ptr<cp::VertexBuffer> createVertexBuffer(const cc::ByteArrayView& data, const cp::VertexLayout& layout) override;
        std::unique_ptr<cp::VertexLayout> createVertexLayout() override;
    };

    ////////////////////////////////////////////////////////////////////////////////////////////////////////
    /// BGFX Uniform
    ///////////////////////////////////////////////////////////////////////////////////////////////////////
    class BgfxUniform : public cp::Uniform
    {
    public:
        explicit BgfxUniform(std::string_view name, cp::Uniform::Type type, int num);

        ~BgfxUniform() override;

        bgfx::UniformHandle getHandle();

        void setColor(const cb::Color& color) override;
        void setTexture(const cp::Texture& texture) override;

    private:
        bgfx::UniformHandle m_handle;
    };

    ////////////////////////////////////////////////////////////////////////////////////////////////////////
    /// BGFX Uniform
    ///////////////////////////////////////////////////////////////////////////////////////////////////////
    class BgfxUniformFactory : public cp::UniformFactory
    {
    public:
        [[nodiscard]] std::shared_ptr<cp::Uniform> createUniform(std::string_view name, cp::Uniform::Type type, int num) override;
    };

    ////////////////////////////////////////////////////////////////////////////////////////////////////////
    /// BGFX Shader
    ///////////////////////////////////////////////////////////////////////////////////////////////////////
    class BgfxShader
    {
    public:
        explicit BgfxShader(const cc::ByteArrayView&);

        BgfxShader(const BgfxShader&) = delete;
        BgfxShader(BgfxShader&&) noexcept;

        BgfxShader& operator=(const BgfxShader&) = delete;
        BgfxShader& operator=(BgfxShader&&) noexcept;

        virtual ~BgfxShader();

        bgfx::ShaderHandle getHandle();

    private:
        bgfx::ShaderHandle m_handle;
    };

    ////////////////////////////////////////////////////////////////////////////////////////////////////////
    /// BGFX Shader
    ///////////////////////////////////////////////////////////////////////////////////////////////////////
    class BgfxProgram : public cp::GpuProgram
    {
    public:
        explicit BgfxProgram(BgfxShader& vsh, BgfxShader& fsh);

        BgfxProgram(const BgfxProgram&) = delete;
        BgfxProgram(BgfxProgram&&) noexcept;

        BgfxProgram& operator=(const BgfxProgram&) = delete;
        BgfxProgram& operator=(BgfxProgram&&) noexcept;

        virtual ~BgfxProgram();

        [[nodiscard]] bgfx::ProgramHandle getHandle() const;

    private:
        bgfx::ProgramHandle m_handle;
    };

    ////////////////////////////////////////////////////////////////////////////////////////////////////////
    /// BGFX Program Factory
    ///////////////////////////////////////////////////////////////////////////////////////////////////////
    class BgfxProgramFactory : public cp::GpuProgramFactory
    {
    public:
        BgfxProgramFactory(BgfxContext&);

        [[nodiscard]] std::shared_ptr<cp::GpuProgram> loadProgramFromFile(std::string_view filename) override;

        [[nodiscard]] std::string getProgramDir() const;

    private:
        struct Program{
            std::filesystem::path file;
            std::shared_ptr<BgfxProgram> program;
        };

        std::vector<Program> m_programs;
        BgfxContext& m_bgfxContext;

        static std::optional<std::string> fileStemToProgramName(std::string_view fileStem);

        BgfxShader loadShader(std::string_view name);
        void loadProgramProgram(std::string_view name);

    };

    ////////////////////////////////////////////////////////////////////////////////////////////////////////
    /// BGFX Texture
    ///////////////////////////////////////////////////////////////////////////////////////////////////////
    class BgfxTexture : public cp::Texture
    {
    public:
        BgfxTexture(int width,
                    int height,
                    bool hasMips,
                    int numLayers,
                    TextureFormat format,
                    cc::Uint64 flags,
                    const cc::ByteArrayView& mem);
        explicit BgfxTexture(std::string_view filePath,
                             uint64_t _flags = 0,
                             Orientation* _orientation = nullptr);

        virtual ~BgfxTexture();

        bgfx::TextureHandle getHandle() const;

    private:
        bgfx::TextureHandle m_handle;

        void load(int width,
                  int height,
                  bool hasMips,
                  int numLayers,
                  TextureFormat format,
                  cc::Uint64 flags,
                  const cc::ByteArrayView& mem);
    };

    ////////////////////////////////////////////////////////////////////////////////////////////////////////
    /// BGFX Texture Factory
    ///////////////////////////////////////////////////////////////////////////////////////////////////////
    class BgfxTextureFactory : public cp::TextureFactory{
    public:
        BgfxTextureFactory();

        std::shared_ptr<cp::Texture> loadTextureFromFile(std::string_view filename) override;

    private:
        struct Texture{
            std::filesystem::path file;
            std::shared_ptr<cp::Texture> texture;
        };

        std::vector<Texture> m_textures;

        void loadTexture(const std::filesystem::path& file);
    };

    ////////////////////////////////////////////////////////////////////////////////////////////////////////
    /// BGFX Context
    ///////////////////////////////////////////////////////////////////////////////////////////////////////
    class BgfxContext
    {
    public:
        explicit BgfxContext(SdlWindowAdapter& wi);
        ~BgfxContext();

        void beginFrame(cc::Vector2ui newSize);
        void endFrame();

        [[nodiscard]] cp::GraphicsApi getApi() const;

    private:
        cc::Vector2ui m_size;

        bool sdlSetWindow(SdlWindowAdapter& win);
    };

    ////////////////////////////////////////////////////////////////////////////////////////////////////////
    /// BGFX Adapter
    ///////////////////////////////////////////////////////////////////////////////////////////////////////
    class BgfxAdapter : public cp::GpuAdapter {
    public:
        explicit BgfxAdapter(SdlWindowAdapter& win);

        void beginFrame(cc::Vector2ui newSize) override;
        void endFrame() override;

        cp::GpuProgramFactory& getProgramFactory() override;
        cp::TextureFactory& getTextureFactory() override;
        cp::UniformFactory& getUniformFactory() override;
        cp::GpuBufferFactory& getBufferFactory() override;

        void setTransform(const cc::Matrix4f&) override;

        void setVertexBuffer(uint8_t stream, const cp::VertexBuffer&) override;
        void setIndexBuffer(const cp::IndexBuffer&) override;
        void submit(const cp::GpuProgram& _program) override;

        void setViewTransform(const cc::Matrix4f &proj, const cc::Matrix4f &view) override;

        void dbgTextPrint(uint16_t _x, uint16_t _y, std::string_view text) override;

        [[nodiscard]] cp::GraphicsApi getApi() const override;

    private:
        BgfxContext m_context;
        BgfxTextureFactory m_textures;
        BgfxProgramFactory m_programs;
        BgfxUniformFactory m_uniforms;
        bgfxGpuBufferFactory m_buffers;
    };
}

#endif //CYBERCRAFT_BGFXADAPTERPRIVATE_H
