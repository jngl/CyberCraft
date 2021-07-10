//
// Created by jngl on 13/05/2021.
//

#ifndef CYBERCRAFT_TEXTUREMANAGER_H
#define CYBERCRAFT_TEXTUREMANAGER_H

<<<<<<< HEAD
#include <Kernel/Texture.h>
=======
#include <Core/Texture.h>
>>>>>>> b0d8808aab9721dbaa8c9afaf9c8a706f1faee8f

#include <string>
#include <filesystem>
#include <vector>

<<<<<<< HEAD
class TextureManager : public ck::TextureManager {
public:
    TextureManager();

    [[nodiscard]] ck::TextureHandle getHandleFromFile(std::string_view filename) override;
    void loadTexture(ck::TextureHandle handle) override;
    void unloadTexture(ck::TextureHandle handle) override;
=======
class TextureManager : public cc::TextureManager {
public:
    TextureManager();

    [[nodiscard]] cc::TextureHandle getHandleFromFile(std::string_view filename) override;
    void loadTexture(cc::TextureHandle handle) override;
    void unloadTexture(cc::TextureHandle handle) override;
>>>>>>> b0d8808aab9721dbaa8c9afaf9c8a706f1faee8f

private:
    struct Texture{
        std::filesystem::path file;
    };

    std::vector<Texture> m_textures;

    void loadTexture(const std::filesystem::path& file);
};

#endif //CYBERCRAFT_TEXTUREMANAGER_H
