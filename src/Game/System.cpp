//
// Created by jngl on 18/07/2020.
//

#include "System.h"

#include "Component.h"
/*
void drawSprite(Scene &scene, Window& win) {
    sf::RenderWindow& sfWin = win.getSFMLWindowsRef();

    auto view = scene.view<PositionComponent, SpriteComponent>();

    sf::Sprite sfSprite;
    sfSprite.setScale(4,4);

    for(auto entity: view){
        auto& pos = view.get<PositionComponent>(entity);
        auto& sprite = view.get<SpriteComponent>(entity);
        if(sprite.texture){
            sfSprite.setPosition(pos.position);
            sfSprite.setTextureRect(sf::IntRect(17*sprite.textureIndex.x, 17*sprite.textureIndex.y, 16, 16));
            sfSprite.setTexture(*sprite.texture);
            sfSprite.setColor(sprite.color);
            sfWin.draw(sfSprite);
        }
    }
}

void movePlayer(Scene &scene) {
    auto view = scene.view<PositionComponent, PlayerComponent>();

    constexpr int speed = 5;

    for(auto entity: view) {
        auto &pos = view.get<PositionComponent>(entity);

        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right)){
            pos.position.x+=speed;
        }

        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left)){
            pos.position.x-=speed;
        }

        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up)){
            pos.position.y-=speed;
        }

        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Down)){
            pos.position.y+=speed;
        }
    }
}
*/