//
// Created by jngl on 18/07/2020.
//

#ifndef CYBERCRAFT_SYSTEM_H
#define CYBERCRAFT_SYSTEM_H

#include "Common.h"

void drawSprite(ccCore::RenderContext& renderContext, ccCore::TextureHandle texture, const ccCore::Vector2f& pos, const component::Sprite& sprite);
void movePlayer(ccCore::Vector2f & pos, const World& world);

#endif //CYBERCRAFT_SYSTEM_H
