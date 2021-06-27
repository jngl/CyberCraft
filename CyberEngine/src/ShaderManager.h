//
// Created by jngl on 06/06/2021.
//

#ifndef CYBERCRAFT_SHADERMANAGER_H
#define CYBERCRAFT_SHADERMANAGER_H

#include "Context.h"

#include <Core/Bases.h>

#include <bgfx/bgfx.h>
#include <vector>
#include <optional>

class ShaderManager : public cc::NonCopyable {
public:
    explicit ShaderManager(Context&);

    bgfx::ProgramHandle get(std::string_view name);

private:
    struct Shader{
        std::string m_name;
        bgfx::ProgramHandle m_program;
    };

    Context& m_context;
    std::vector<Shader> m_shaders;

    void loadShader();
    static std::optional<std::string> fileStemToShaderName(std::string_view fileStem);

    bgfx::ShaderHandle loadShader(std::string_view name);
    bgfx::ProgramHandle loadShaderProgram(std::string_view name);
};


#endif //CYBERCRAFT_SHADERMANAGER_H
