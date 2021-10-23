//
// Created by jngl on 11/07/2021.
//

#ifndef CYBERCRAFT_BGFXADAPTER_H
#define CYBERCRAFT_BGFXADAPTER_H

#include <Kernel/Engine.h>
#include <Core/Memory.h>

#include <bgfx/bgfx.h>

#include <filesystem>

#include "Enum.h"

namespace bgfx
{
    struct ProgramHandle;
}

namespace cc{
    template<class T>
    struct Vector2;

    using Vector2ui = Vector2<unsigned int>;
}

namespace cg::Impl {
    class SdlWindowAdapter;
    class BgfxAdapter;
    class VertexLayout;
    class BgfxContext;

    ////////////////////////////////////////////////////////////////////////////////////////////////////////
    /// Index Buffer
    ///////////////////////////////////////////////////////////////////////////////////////////////////////
    class IndexBuffer{
    public:
        explicit IndexBuffer(const cc::ByteArrayView&);
        ~IndexBuffer();

        [[nodiscard]] bgfx::IndexBufferHandle getBgfxHandle() const;

    private:
        bgfx::IndexBufferHandle m_handle;
    };

    ////////////////////////////////////////////////////////////////////////////////////////////////////////
    /// Vertex Buffer
    ///////////////////////////////////////////////////////////////////////////////////////////////////////
    class VertexBuffer{
    public:
        VertexBuffer(const cc::ByteArrayView& data, const VertexLayout& layout);
        ~VertexBuffer();

        [[nodiscard]] bgfx::VertexBufferHandle getBgfxHandle() const;

    private:
        bgfx::VertexBufferHandle m_handle;
    };

    ////////////////////////////////////////////////////////////////////////////////////////////////////////
    /// Vertex Layout
    ///////////////////////////////////////////////////////////////////////////////////////////////////////
    class VertexLayout{
    public:
        void begin();
        void add(Attrib attrib, uint8_t num, AttribType type, bool normalized = false, bool asInt = false);
        void end();

        [[nodiscard]] const bgfx::VertexLayout& getBgfxLayout() const;

    private:
        bgfx::VertexLayout m_layout;
    };

    ////////////////////////////////////////////////////////////////////////////////////////////////////////
    /// BGFX Uniform
    ///////////////////////////////////////////////////////////////////////////////////////////////////////
    class BgfxUniform
    {
    public:
        explicit BgfxUniform(std::string_view name, UniformType type, int num);

        BgfxUniform(const BgfxUniform&) = delete;
        BgfxUniform(BgfxUniform&&) noexcept;

        BgfxUniform& operator=(const BgfxUniform&) = delete;
        BgfxUniform& operator=(BgfxUniform&&) noexcept;

        virtual ~BgfxUniform();

        bgfx::UniformHandle getHandle();

        void setColor(const cc::Color&);

    private:
        bgfx::UniformHandle m_handle;
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
    class BgfxProgram
    {
    public:
        explicit BgfxProgram(BgfxShader& vsh, BgfxShader& fsh);

        BgfxProgram(const BgfxProgram&) = delete;
        BgfxProgram(BgfxProgram&&) noexcept;

        BgfxProgram& operator=(const BgfxProgram&) = delete;
        BgfxProgram& operator=(BgfxProgram&&) noexcept;

        virtual ~BgfxProgram();

        bgfx::ProgramHandle getHandle() const;

    private:
        bgfx::ProgramHandle m_handle;
    };

    ////////////////////////////////////////////////////////////////////////////////////////////////////////
    /// BGFX Program Factory
    ///////////////////////////////////////////////////////////////////////////////////////////////////////
    class BgfxProgramFactory
    {
    public:
        BgfxProgramFactory(BgfxContext&);

        [[nodiscard]] std::shared_ptr<BgfxProgram> loadProgramFromFile(std::string_view filename);

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
    class BgfxTexture : public ck::Texture
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
    class BgfxTextureFactory : public ck::TextureFactory{
    public:
        BgfxTextureFactory();

        std::shared_ptr<ck::Texture> loadTextureFromFile(std::string_view filename) override;

    private:
        struct Texture{
            std::filesystem::path file;
            std::shared_ptr<ck::Texture> texture;
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

        [[nodiscard]] ck::GraphicsApi getApi() const;

    private:
        cc::Vector2ui m_size;

        bool sdlSetWindow(SdlWindowAdapter& win);
    };

    ////////////////////////////////////////////////////////////////////////////////////////////////////////
    /// BGFX Adapter
    ///////////////////////////////////////////////////////////////////////////////////////////////////////
    class BgfxAdapter {
    public:
        explicit BgfxAdapter(SdlWindowAdapter& win);

        void beginFrame(cc::Vector2ui newSize);
        void endFrame();

        BgfxProgramFactory& getProgramFactory();

        void setTransform(const cc::Matrix4f&);

        void setVertexBuffer(uint8_t stream, const VertexBuffer&);
        void setIndexBuffer(const IndexBuffer&);
        void submit(const BgfxProgram& _program);

        [[nodiscard]] ck::GraphicsApi getApi() const;

    private:
        BgfxContext m_context;
        BgfxTextureFactory m_textures;
        BgfxProgramFactory m_programs;
    };
}

#endif //CYBERCRAFT_BGFXADAPTER_H
