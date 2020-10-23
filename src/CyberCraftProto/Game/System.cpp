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

void movePlayer(ccCore::Vector2f& pos, const World& world) {
    auto funcMove = [&pos, &world](sf::Keyboard::Key key, ccCore::Vector2f move){
        if(!sf::Keyboard::isKeyPressed(key)){
            return;
        }

        ccCore::Vector2f newPos = pos + move;

        if(!newPos.isInRect(0, World::sizeX-1, 0, World::sizeY-1)){
            return;
        }

        ccCore::Vector2i newPosInt = (newPos + ccCore::Vector2f{0.5f, 0.8f}).toVector<int>();
        const BlocInfo* blocInfo = world.getBloc(newPosInt);
        if(!blocInfo || blocInfo->group.collision) {
            return;
        }

        pos = newPos;
    };

    constexpr float speed = 0.1f;

    funcMove(sf::Keyboard::Right, {speed, 0});
    funcMove(sf::Keyboard::Left, {-speed, 0});
    funcMove(sf::Keyboard::Up, {0, -speed});
    funcMove(sf::Keyboard::Down, {0, speed});
}
