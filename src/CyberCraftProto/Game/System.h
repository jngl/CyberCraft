//
// Created by jngl on 18/07/2020.
//

#ifndef CYBERCRAFT_SYSTEM_H
#define CYBERCRAFT_SYSTEM_H

#include "Common.h"
#include "Core/pointer.h"
#include "Kernel/Engine2D.h"

void drawSprite(cc::Ref<ck::SpriteDrawer> renderContext, ck::TextureHandle texture, const cc::Vector2f& pos, const component::Sprite& sprite);

void movePlayer(cc::Ref<cc::Vector2f> pos, const World& world);

#endif //CYBERCRAFT_SYSTEM_H
