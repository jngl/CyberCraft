//
// Created by jngl on 11/07/2021.
//

#ifndef CYBERCRAFT_BGFXADAPTER_H
#define CYBERCRAFT_BGFXADAPTER_H

#include <Kernel/Engine.h>
#include <Core/Memory.h>

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
