//
// Created by jngl on 13/05/2021.
//

#include "TextureManager.h"

#include <filesystem>
#include <iostream>
#include <algorithm>

TextureManager::TextureManager() {
    namespace fs = std::filesystem;
    for(const auto& p: fs::directory_iterator("data")){
        loadTexture(p.path());
    }
}

void TextureManager::loadTexture(const std::filesystem::path& file) {
    if(file.extension() != ".dds" && file.extension() != ".png"){
        return;
    }

    m_textures.push_back(Texture{file});

    std::cout<<"load texture : "<<file.stem()<<"\n";
}

<<<<<<< HEAD
ck::TextureHandle TextureManager::getHandleFromFile(std::string_view filename) {
=======
cc::TextureHandle TextureManager::getHandleFromFile(std::string_view filename) {
>>>>>>> b0d8808aab9721dbaa8c9afaf9c8a706f1faee8f
    auto isFileNameCorrect = [filename](const Texture& texture) -> bool{
        return texture.file.stem() == filename;
    };

    auto it = std::find_if(m_textures.begin(), m_textures.end(), isFileNameCorrect);

    if(it == std::end(m_textures)){
<<<<<<< HEAD
        return ck::TextureHandle();
=======
        return cc::TextureHandle();
>>>>>>> b0d8808aab9721dbaa8c9afaf9c8a706f1faee8f
    }

    unsigned int index = static_cast<unsigned int>(it - std::begin(m_textures));

<<<<<<< HEAD
    return ck::TextureHandle(index);
}

void TextureManager::loadTexture(ck::TextureHandle /*unused*/) {
}

void TextureManager::unloadTexture(ck::TextureHandle /*unused*/) {
=======
    return cc::TextureHandle(index);
}

void TextureManager::loadTexture(cc::TextureHandle /*unused*/) {
}

void TextureManager::unloadTexture(cc::TextureHandle /*unused*/) {
>>>>>>> b0d8808aab9721dbaa8c9afaf9c8a706f1faee8f
}
