//
// Created by jngl on 29/08/2020.
//

#ifndef CYBERCRAFT_WINDOWSFML_H
#define CYBERCRAFT_WINDOWSFML_H

#include <Core/Window.h>

#include <memory>
#include <SFML/Graphics.hpp>
#include <map>

class WindowSfmlImpl;

class WindowSFML : public Window {
public:
    WindowSFML();
    ~WindowSFML() override;

    [[nodiscard]] bool isOpen() const override;

    void beginFrame() override;
    void endFrame() override;

    TextureHandle loadTexture(std::string_view filename) override;
    void unloadTexture(TextureHandle texture) override;

    void drawSprite(TextureHandle texture,
                            const math::Vector2f& pos,
                            const math::Vector2i& textureIndex,
                            Color color,
                            Color backgroundColor) override;

    void drawSprite(TextureHandle texture,
                            const math::Vector2f& pos,
                            float scale,
                            Color color) override;

private:
    std::map<TextureHandle, std::unique_ptr<sf::Texture>> m_texture;
    int m_nextId = 1;
    sf::RenderWindow m_window;
    sf::View m_view;
};



#endif //CYBERCRAFT_WINDOWSFML_H
