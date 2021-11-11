//
// Created by jngl on 06/11/2021.
//

#ifndef CYBERCRAFT_GPUPROGRAM_H
#define CYBERCRAFT_GPUPROGRAM_H

#include <Core/Bases.h>

namespace cc
{
    struct Color;
}

namespace cp
{
    class Texture;
}

namespace ck
{
    class Uniform : public cc::NonCopyable
    {
    public:
        enum class Type
        {
            Sampler,

            Vec4,
            Mat3,
            Mat4,

            Count
        };

        virtual void setColor(const cc::Color&) = 0;
        virtual void setTexture(const cp::Texture&) = 0;
    };

    class UniformFactory : public cc::NonCopyable
    {
    public:
        [[nodiscard]] virtual std::shared_ptr<Uniform> createUniform(std::string_view name, Uniform::Type type, int num) = 0;
    };

    class GpuProgram : public cc::NonCopyable
    {
    public:
        virtual ~GpuProgram() = default;
    };

    class GpuProgramFactory : public cc::NonCopyable
    {
    public:
        [[nodiscard]] virtual std::shared_ptr<GpuProgram> loadProgramFromFile(std::string_view filename) = 0;
    };
}

#endif //CYBERCRAFT_GPUPROGRAM_H
