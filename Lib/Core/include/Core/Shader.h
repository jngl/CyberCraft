//
// Created by jngl on 02/07/2021.
//

#ifndef CYBERCRAFT_SHADER_H
#define CYBERCRAFT_SHADER_H

#include <Core/Id.h>
#include <Core/Bases.h>

namespace cc
{
    using ShaderHandle = Id<unsigned int, struct ShaderHandleTag>;

    class ShaderManager : public NonCopyable{
    public:
        [[nodiscard]] virtual ShaderHandle getHandleFromFile(std::string_view filename) = 0;
        virtual void loadShader(ShaderHandle) = 0;
        virtual void unloadShader(ShaderHandle) = 0;
    };
}

#endif //CYBERCRAFT_SHADERMANAGER_H
