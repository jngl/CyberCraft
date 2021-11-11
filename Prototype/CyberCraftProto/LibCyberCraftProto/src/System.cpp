//
// Created by jngl on 18/07/2020.
//

#include "System.h"

#include "Component.h"
#include "World.h"

#include <Kernel/Engine2D.h>

void drawSprite(cc::Ref<ck::SpriteDrawer> renderContext, const cp::Texture& texture, const cc::Vector2f& pos, const component::Sprite& sprite) {
    renderContext->drawSprite(texture, pos, sprite.textureIndex, sprite.color, sprite.backgroundColor, sprite.rotation);
}

void movePlayer(cc::Ref<ck::Window> win,cc::Ref<cc::Vector2f> pos, const World& world) {

    auto funcMove = [&win, &pos, &world](ck::Key key, cc::Vector2f move){
        if(!win->isKeyPressed(key)){
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

    funcMove(ck::Key::RIGHT, {speed, 0});
    funcMove(ck::Key::LEFT, {-speed, 0});
    funcMove(ck::Key::UP, {0, -speed});
    funcMove(ck::Key::DOWN, {0, speed});
}
