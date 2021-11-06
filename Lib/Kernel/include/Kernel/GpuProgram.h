//
// Created by jngl on 06/11/2021.
//

#ifndef CYBERCRAFT_GPUPROGRAM_H
#define CYBERCRAFT_GPUPROGRAM_H

namespace ck
{
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
