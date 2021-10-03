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
        explicit BgfxShader(const cc::ByteArray&);

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

        bgfx::ProgramHandle getHandle();

    private:
        bgfx::ProgramHandle m_handle;
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
                    const cc::ByteArray& mem);
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
                  const cc::ByteArray& mem);
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
    /// BGFX Adapter
    ///////////////////////////////////////////////////////////////////////////////////////////////////////
    class BgfxAdapter {
    public:
        explicit BgfxAdapter(SdlWindowAdapter& win);

        void beginFrame(cc::Vector2ui newSize);
        void endFrame();

        [[nodiscard]] ck::GraphicsApi getApi() const;

    private:
        cc::Vector2ui m_size;

        bool sdlSetWindow(SdlWindowAdapter& win);
    };
}

#endif //CYBERCRAFT_BGFXADAPTER_H
