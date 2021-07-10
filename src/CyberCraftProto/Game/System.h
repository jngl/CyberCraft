//
// Created by jngl on 18/07/2020.
//

#ifndef CYBERCRAFT_SYSTEM_H
#define CYBERCRAFT_SYSTEM_H

#include "Common.h"
#include "Core/pointer.h"
<<<<<<< HEAD
#include "Kernel/Engine2D.h"

void drawSprite(cc::Ref<ck::SpriteDrawer> renderContext, ck::TextureHandle texture, const cc::Vector2f& pos, const component::Sprite& sprite);
=======
#include "Core/Engine2D.h"

void drawSprite(cc::Ref<cc::SpriteDrawer> renderContext, cc::TextureHandle texture, const cc::Vector2f& pos, const component::Sprite& sprite);
>>>>>>> b0d8808aab9721dbaa8c9afaf9c8a706f1faee8f
void movePlayer(cc::Ref<cc::Vector2f> pos, const World& world);

#endif //CYBERCRAFT_SYSTEM_H
