//
// Created by jngl on 06/06/2021.
//

#ifndef CYBERCRAFT_SHADERMANAGER_H
#define CYBERCRAFT_SHADERMANAGER_H

#include "Context.h"

#include <Core/Bases.h>
#include <Core/Shader.h>

#include <bgfx/bgfx.h>
#include <vector>
#include <optional>
#include <filesystem>

class ShaderManager : public cc::ShaderManager {
public:
    explicit ShaderManager(Context&);

    bgfx::ProgramHandle get(cc::ShaderHandle);

    [[nodiscard]] cc::ShaderHandle getHandleFromFile(std::string_view filename) override;
    void loadShader(cc::ShaderHandle handle) override;
    void unloadShader(cc::ShaderHandle handle) override;

    std::string getShaderDir() const;

private:
    struct Shader{
        std::string name;
        bgfx::ProgramHandle m_program;
    };

    Context& m_context;
    std::vector<Shader> m_shaders;

    static std::optional<std::string> fileStemToShaderName(std::string_view fileStem);

    bgfx::ShaderHandle loadShader(std::string_view name);
    void loadShaderProgram(std::string_view name);
};


#endif //CYBERCRAFT_SHADERMANAGER_H
