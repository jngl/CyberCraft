//
// Created by jngl on 13/05/2021.
//

#ifndef CYBERCRAFT_TEXTUREMANAGER_H
#define CYBERCRAFT_TEXTUREMANAGER_H

#include <Kernel/Texture.h>

#include <string>
#include <filesystem>
#include <vector>

class TextureManager : public ck::TextureManager {
public:
    TextureManager();

    [[nodiscard]] ck::TextureHandle getHandleFromFile(std::string_view filename) override;
    void loadTexture(ck::TextureHandle handle) override;
    void unloadTexture(ck::TextureHandle handle) override;

private:
    struct Texture{
        std::filesystem::path file;
    };

    std::vector<Texture> m_textures;

    void loadTexture(const std::filesystem::path& file);
};

#endif //CYBERCRAFT_TEXTUREMANAGER_H
