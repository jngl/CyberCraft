//
// Created by jngl on 06/06/2021.
//

#include "ShaderManager.h"

#include <iostream>
#include <filesystem>
#include <string>
#include <string_view>

Shader::Shader(std::string_view name):
    m_name(name){
    std::cout<<"load shader "<<m_name<<std::endl;
}

Shader::~Shader() {
    std::cout<<"Unload Shader "<<m_name<<std::endl;
}

Shader::Shader(Shader && other):
    m_name(other.m_name)
{
    other.m_name = "";
}

ShaderManager::ShaderManager(Context& ctx):
    m_context(ctx)
{
    loadShader();
}

void ShaderManager::loadShader() {
    std::string_view shaderType = GetGraphicsApiShaderType(m_context.getApi());
    std::string shaderDir = std::string("data/shader/") + std::string(shaderType);

    namespace fs = std::filesystem;
    for (const auto &p: fs::directory_iterator(shaderDir)) {
        auto name = fileStemToShaderName(p.path().stem().string());
        if(name.has_value()){
            m_shaders.emplace_back(name.value());
        }
    }
}

std::optional<std::string> ShaderManager::fileStemToShaderName(std::string_view fileStem) {
    size_t indexUnderscore = fileStem.find('_');
    if (indexUnderscore == std::string::npos) {
        return {};
    }

    std::string prefix(fileStem.substr(0, indexUnderscore));
    std::string name(fileStem.substr(indexUnderscore + 1));

    if (prefix != "vs") {
        return {};
    }

    return {name};
}
