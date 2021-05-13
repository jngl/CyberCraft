//
// Created by jngl on 13/05/2021.
//

#ifndef CYBERCRAFT_TEXTUREMANAGER_H
#define CYBERCRAFT_TEXTUREMANAGER_H

#include <Core/Texture.h>

#include <string>
#include <filesystem>
#include <vector>

class TextureManager : public cc::TextureManager {
public:
    TextureManager();

    [[nodiscard]] cc::TextureHandle getHandleFromFile(std::string_view filename) override;
    void loadTexture(cc::TextureHandle handle) override;
    void unloadTexture(cc::TextureHandle handle) override;

private:
    struct Texture{
        std::filesystem::path file;
    };

    std::vector<Texture> m_textures;

    void loadTexture(const std::filesystem::path& file);
};

#endif //CYBERCRAFT_TEXTUREMANAGER_H
