//
// Created by jngl on 06/06/2021.
//

#ifndef CYBERCRAFT_SHADERMANAGER_H
#define CYBERCRAFT_SHADERMANAGER_H

#include "Context.h"

#include <Core/Bases.h>

class Shader : public cc::NonCopyable {
public:
    Shader(std::string_view name);
    Shader(Shader&&);
    ~Shader();

private:
    std::string m_name;
};

class ShaderManager : public cc::NonCopyable {
public:
    explicit ShaderManager(Context&);

private:
    Context& m_context;
    std::vector<Shader> m_shaders;

    void loadShader();
    static std::optional<std::string> fileStemToShaderName(std::string_view fileStem);
};


#endif //CYBERCRAFT_SHADERMANAGER_H
