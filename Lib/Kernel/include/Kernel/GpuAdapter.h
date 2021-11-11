//
// Created by jngl on 11/11/2021.
//

#ifndef CYBERCRAFT_GPUADAPTER_H
#define CYBERCRAFT_GPUADAPTER_H

#include <Core/Bases.h>

#include "Engine.h"

namespace cc{
    template<class T>
    struct Vector2;

    using Vector2ui = Vector2<unsigned int>;

    template<class T>
    struct Matrix4;

    using Matrix4f = Matrix4<float>;
}

namespace cp
{
    class TextureFactory;
}

namespace ck
{
    class GpuProgram;
    class GpuProgramFactory;
    class UniformFactory;
    class VertexBuffer;
    class IndexBuffer;
    class GpuBufferFactory;

    class GpuAdapter : public cc::NonCopyable
    {
    public:
        virtual void beginFrame(cc::Vector2ui newSize) = 0;
        virtual void endFrame() = 0;

        virtual GpuProgramFactory& getProgramFactory() = 0;
        virtual cp::TextureFactory& getTextureFactory() = 0;
        virtual UniformFactory& getUniformFactory() = 0;
        virtual GpuBufferFactory& getBufferFactory() = 0;

        virtual void setTransform(const cc::Matrix4f&) = 0;

        virtual void setVertexBuffer(uint8_t stream, const VertexBuffer&) = 0;
        virtual void setIndexBuffer(const IndexBuffer&) = 0;
        virtual void submit(const ck::GpuProgram& _program) = 0;

        virtual void setViewTransform(const cc::Matrix4f &proj, const cc::Matrix4f &view) = 0;

        virtual void dbgTextPrint(uint16_t _x, uint16_t _y, std::string_view text) = 0;

        [[nodiscard]] virtual ck::GraphicsApi getApi() const = 0;
    };
}

#endif //CYBERCRAFT_GPUADAPTER_H
