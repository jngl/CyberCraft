//
// Created by jngl on 18/07/2020.
//

#ifndef CYBERCRAFT_SYSTEMIMPL_H
#define CYBERCRAFT_SYSTEM_H

#include "Core/pointer.h"
#include "Kernel/Engine2D.h"

class World;

namespace component{
    class Sprite;
}

void drawSprite(cc::Ref<ck::SpriteDrawer> renderContext, ck::TextureHandle texture, const cc::Vector2f& pos, const component::Sprite& sprite);

void movePlayer(cc::Ref<cc::Vector2f> pos, const World& world);

#endif //CYBERCRAFT_SYSTEMIMPL_H
