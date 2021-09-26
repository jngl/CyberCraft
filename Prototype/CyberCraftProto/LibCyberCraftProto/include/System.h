//
// Created by jngl on 18/07/2020.
//

#ifndef CYBERCRAFT_SYSTEMIMPL_H
#define CYBERCRAFT_SYSTEM_H

#include "Core/pointer.h"
#include "Kernel/Engine2D.h"
#include "Kernel/Window.h"

class World;

namespace component{
    class Sprite;
}

void drawSprite(cc::Ref<ck::SpriteDrawer> renderContext, const ck::Texture& texture, const cc::Vector2f& pos, const component::Sprite& sprite);

void movePlayer(cc::Ref<ck::Window> win, cc::Ref<cc::Vector2f> pos, const World& world);

#endif //CYBERCRAFT_SYSTEMIMPL_H
