//
// Created by jngl on 18/07/2020.
//

#include "System.h"

#include "Component.h"
#include "World.h"

#include <Core/Window.h>

void drawSprite(Window& win, const sf::Texture& texture, const sf::Vector2f& pos, const component::Sprite& sprite) {
    sf::RectangleShape background;
    background.setPosition(pos*32.f);
    background.setSize(sf::Vector2f(32,32));
    background.setFillColor(sprite.backgroundColor);
    win.getSFMLWindowsRef().draw(background);


    sf::Sprite sfSprite;
    sfSprite.setScale(2,2);

    sfSprite.setPosition(pos*32.f);
    sfSprite.setTextureRect(sf::IntRect(17*sprite.textureIndex.x, 17*sprite.textureIndex.y, 16, 16));
    sfSprite.setTexture(texture);
    sfSprite.setColor(sprite.color);
    win.getSFMLWindowsRef().draw(sfSprite);
}


void movePlayer(sf::Vector2f& pos, component::Player& player, const World& world) {
    if(player.timerMove>0){
        --player.timerMove;
        return;
    }

    constexpr int nbTickMove = 5;

    player.timerMove = nbTickMove;

    auto funcMove = [&pos, &world](sf::Keyboard::Key key, int moveX, int moveY){
        int newPosX = static_cast<int>(pos.x) + moveX;
        int newPosY = static_cast<int>(pos.y) + moveY;
        if(sf::Keyboard::isKeyPressed(key) && !getBlocInfo(world.getBloc(newPosX, newPosY)).collision){
            pos.x += static_cast<float>(moveX);
            pos.y += static_cast<float>(moveY);
        }
    };
    funcMove(sf::Keyboard::Right, 1, 0);
    funcMove(sf::Keyboard::Left, -1, 0);
    funcMove(sf::Keyboard::Up, 0, -1);
    funcMove(sf::Keyboard::Down, 0, 1);
}
