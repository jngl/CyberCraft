//
// Created by jngl on 18/07/2020.
//

#ifndef CYBERCRAFT_SYSTEM_H
#define CYBERCRAFT_SYSTEM_H

#include "Common.h"

void drawSprite(cc::RenderContext& renderContext, cc::TextureHandle texture, const cc::Vector2f& pos, const component::Sprite& sprite);
void movePlayer(cc::Vector2f & pos, const World& world);

#endif //CYBERCRAFT_SYSTEM_H
