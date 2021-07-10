//
// Created by jngl on 06/06/2021.
//

#include "ShaderManager.h"

#include "Context.h"

#include <iostream>
#include <filesystem>
#include <string>
#include <string_view>
#include <algorithm>

#include <bx/readerwriter.h>
#include <bx/file.h>

// TODO temporary
static const bgfx::Memory* loadMem(bx::FileReaderI* _reader, const char* _filePath)
{
    if (bx::open(_reader, _filePath) )
    {
        uint32_t size = (uint32_t)bx::getSize(_reader);
        const bgfx::Memory* mem = bgfx::alloc(size+1);
        bx::read(_reader, mem->data, size);
        bx::close(_reader);
        mem->data[mem->size-1] = '\0';
        return mem;
    }

    std::cout<<"Failed to load "<< _filePath<<std::endl;
    return nullptr;
}

static bx::FileReaderI* s_fileReader = NULL;

ShaderManager::ShaderManager(Context& ctx):
    m_context(ctx)
{
    s_fileReader = new bx::FileReader();

    namespace fs = std::filesystem;
    for (const auto &p: fs::directory_iterator(getShaderDir())) {
        auto name = fileStemToShaderName(p.path().stem().string());
        if(name.has_value()){
            loadShaderProgram(name.value());
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

bgfx::ShaderHandle ShaderManager::loadShader(std::string_view name) {
    std::string filePath = "./data/shader/" + std::string(GetGraphicsApiShaderType(m_context.getApi())) + "/" + std::string(name) + ".bin";

    bgfx::ShaderHandle handle = bgfx::createShader(loadMem(s_fileReader, filePath.c_str()) );
    bgfx::setName(handle, std::string(name).c_str());

    return handle;
}

void ShaderManager::loadShaderProgram(std::string_view name) {
    std::cout<<"load shader "<<name<<std::endl;

    bgfx::ShaderHandle vsh = loadShader(std::string("vs_")+std::string(name));
    bgfx::ShaderHandle fsh = loadShader(std::string("fs_")+std::string(name));

    bgfx::ProgramHandle program = bgfx::createProgram(vsh, fsh, true);

    m_shaders.push_back(Shader{std::string(name), program});
}

bgfx::ProgramHandle ShaderManager::get(ck::ShaderHandle handle) {
    if(handle.value() < 0 || handle.value() >= m_shaders.size()){
        return bgfx::ProgramHandle();
    }

    return m_shaders[handle.value()].m_program;
}

ck::ShaderHandle ShaderManager::getHandleFromFile(std::string_view filename) {
    auto isFileNameCorrect = [filename](const Shader& shader) -> bool{
        return shader.name == filename;
    };

    auto it = std::find_if(m_shaders.begin(), m_shaders.end(), isFileNameCorrect);

    if(it == std::end(m_shaders)){
        return ck::ShaderHandle();
    }

    unsigned int index = static_cast<unsigned int>(it - std::begin(m_shaders));

    return ck::ShaderHandle(index);
}

void ShaderManager::loadShader(ck::ShaderHandle /*handle*/) {

}

void ShaderManager::unloadShader(ck::ShaderHandle /*handle*/) {

}

std::string ShaderManager::getShaderDir() const {
    std::string shaderType(GetGraphicsApiShaderType(m_context.getApi()));
    return "data/shader/" + shaderType;
}
