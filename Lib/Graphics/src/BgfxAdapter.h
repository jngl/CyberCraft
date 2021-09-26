//
// Created by jngl on 11/07/2021.
//

#ifndef CYBERCRAFT_BGFXADAPTER_H
#define CYBERCRAFT_BGFXADAPTER_H

#include <Kernel/Engine.h>
#include <Core/Memory.h>

#include <bgfx/bgfx.h>

#include <filesystem>

#include "TextureEnum.h"

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

    using ShaderHandle = cc::Id<unsigned int, struct ShaderHandleTag>;
    using ProgramHandle = cc::Id<unsigned int, struct ProgramHandleTag>;

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

    class BgfxAdapter {
    public:
        explicit BgfxAdapter(SdlWindowAdapter& win);

        ShaderHandle createShader(const cc::ByteArray& mem);
        ProgramHandle createProgram(ShaderHandle vsh, ShaderHandle fsh, bool destroyShaders);

        void beginFrame(cc::Vector2ui newSize);
        void endFrame();

        [[nodiscard]] ck::GraphicsApi getApi() const;

    private:
        cc::Vector2ui m_size;

        bool sdlSetWindow(SdlWindowAdapter& win);
    };
}

#endif //CYBERCRAFT_BGFXADAPTER_H
