//
// Created by jngl on 18/07/2020.
//

#include "System.h"

#include "Component.h"
#include "World.h"

#include <Core/RenderContext.h>

#include <SFML/Window.hpp>

void drawSprite(ccCore::RenderContext& ctx, ccCore::TextureHandle texture, const ccCore::Vector2f& pos, const component::Sprite& sprite) {
    ctx.drawSprite(texture, pos, sprite.textureIndex, sprite.color, sprite.backgroundColor, sprite.rotation);
}

void movePlayer(ccCore::Vector2f& pos, component::Player& player, const World& world) {
    if(player.timerMove>0){
        --player.timerMove;
        return;
    }

    constexpr int nbTickMove = 5;

    player.timerMove = nbTickMove;

    auto funcMove = [&pos, &world](sf::Keyboard::Key key, int moveX, int moveY){
        if(!sf::Keyboard::isKeyPressed(key)){
            return;
        }

        int newPosX = static_cast<int>(pos.x) + moveX;
        int newPosY = static_cast<int>(pos.y) + moveY;

        if(newPosX<0 || newPosX>=World::sizeX){
            return;
        }

        if(newPosY<0 || newPosY>=World::sizeY){
            return;
        }

        const BlocInfo* blocInfo = world.getBloc(newPosX, newPosY);
        if(!blocInfo || blocInfo->group.collision) {
            return;
        }

        pos.x += static_cast<float>(moveX);
        pos.y += static_cast<float>(moveY);
    };
    funcMove(sf::Keyboard::Right, 1, 0);
    funcMove(sf::Keyboard::Left, -1, 0);
    funcMove(sf::Keyboard::Up, 0, -1);
    funcMove(sf::Keyboard::Down, 0, 1);
}
