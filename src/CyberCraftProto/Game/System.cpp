//
// Created by jngl on 18/07/2020.
//

#include "System.h"

#include "Component.h"
#include "World.h"

#include <Core/RenderContext.h>

#include <SFML/Window.hpp>

void drawSprite(cc::Ref<cc::RenderContext2D> renderContext, cc::TextureHandle texture, const cc::Vector2f& pos, const component::Sprite& sprite) {
    renderContext->drawSprite(texture, pos, sprite.textureIndex, sprite.color, sprite.backgroundColor, sprite.rotation);
}

void movePlayer(cc::Ref<cc::Vector2f> pos, const World& world) {
    auto funcMove = [&pos, &world](sf::Keyboard::Key key, cc::Vector2f move){
        if(!sf::Keyboard::isKeyPressed(key)){
            return;
        }

        cc::Vector2f newPos = *pos + move;

        if(!newPos.isInRect(0, World::sizeX-1, 0, World::sizeY-1)){
            return;
        }

        constexpr cc::Vector2f collisionPoint{0.5f, 0.8f};
        cc::Vector2i newPosInt = (newPos + collisionPoint).toVector<int>();
        const Bloc bloc = world.getBloc(newPosInt);
        if(getBlocGroupInfo(getBlocInfo(bloc).group).collision) {
            return;
        }

        *pos = newPos;
    };

    constexpr float speed = 0.1f;

    funcMove(sf::Keyboard::Right, {speed, 0});
    funcMove(sf::Keyboard::Left, {-speed, 0});
    funcMove(sf::Keyboard::Up, {0, -speed});
    funcMove(sf::Keyboard::Down, {0, speed});
}
