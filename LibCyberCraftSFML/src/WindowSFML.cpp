//
// Created by jngl on 29/08/2020.
//

#include "CyberCraftSFML/WindowSFML.h"

#include "conversion.h"

#include <Core/Color.h>

#include <SFML/Graphics.hpp>
#include <map>


class WindowSfmlImpl : public GraphicsContext
{
public:
    explicit WindowSfmlImpl():
            m_window(sf::VideoMode(800, 600), "Cyber Craft")
    {
        m_window.setFramerateLimit(60);
        m_window.setView(m_view);
    }

    TextureHandle loadTexture(std::string_view filename) override{
        TextureHandle textureHandle{m_nextId++};
        std::unique_ptr<sf::Texture>& texturePtr =  m_texture[textureHandle];
        texturePtr = std::make_unique<sf::Texture>();
        texturePtr->loadFromFile(std::string(filename));
        return textureHandle;
    }

    void unloadTexture(TextureHandle texture) override{
        m_texture.erase(texture);
    }

    void drawSprite(TextureHandle textureHandle,
                    const math::Vector2f& pos,
                    const math::Vector2i& textureIndex,
                    Color color,
                    Color backgroundColor) override {
        sf::Texture& texture = *m_texture[textureHandle];

        math::Vector2f a;

        sf::RectangleShape background;
        background.setPosition(toSfVector2(pos * 32.f));
        background.setSize(sf::Vector2f(32,32));
        background.setFillColor(toSfColor(backgroundColor));
        m_window.draw(background);

        sf::Sprite sfSprite;
        sfSprite.setScale(2,2);

        sfSprite.setPosition(toSfVector2(pos*32.f));
        sfSprite.setTextureRect(sf::IntRect(17*textureIndex.x, 17*textureIndex.y, 16, 16));
        sfSprite.setTexture(texture);
        sfSprite.setColor(toSfColor(color));
        m_window.draw(sfSprite);
    }

    virtual void drawSprite(TextureHandle textureHandle,
                            const math::Vector2f& pos,
                            float scale,
                            Color color) override {
        sf::Texture& texture = *m_texture[textureHandle];
        sf::Sprite sfSprite;
        sfSprite.setTexture(texture);
        sfSprite.setPosition(toSfVector2(pos));
        sfSprite.setScale(scale, scale);
        sfSprite.setColor(toSfColor(color));
        m_window.draw(sfSprite);
    }

    bool isOpen() const {
        return m_window.isOpen();
    }

    void beginFrame(){
        //input event
        sf::Event event{};
        while (m_window.pollEvent(event)) {
            switch (event.type) {
                case sf::Event::Closed:
                    m_window.close();
                    break;
                case sf::Event::Resized:
                    m_view.setSize(event.size.width, event.size.height);
                    m_view.setCenter(static_cast<float>(event.size.width)/2,static_cast<float>(event.size.height)/2);
                    m_window.setView(m_view);
                    break;
                default:
                    break;
            }
        }

        //clear
        m_window.clear(sf::Color::Black);
    }
    void endFrame(){
        m_window.display();
    }

private:
    std::map<TextureHandle, std::unique_ptr<sf::Texture>> m_texture;
    int m_nextId = 1;
    sf::RenderWindow m_window;
    sf::View m_view;
};

WindowSFML::WindowSFML()
{
    m_impl = std::make_unique<WindowSfmlImpl>();
}

bool WindowSFML::isOpen() const {
    return m_impl->isOpen();
}

void WindowSFML::beginFrame() {
   m_impl->beginFrame();
}

void WindowSFML::endFrame() {
    m_impl->endFrame();
}

GraphicsContext &WindowSFML::getGraphicsContext() {
    return *m_impl;
}

WindowSFML::~WindowSFML() = default;

