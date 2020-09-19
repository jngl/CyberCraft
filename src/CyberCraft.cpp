//
// Created by jngl on 18/08/2020.
//

#include "CyberCraft.h"

#include "Game/System.h"

#include <Core/Error.h>

const char* gameMap =
        "~~~~~~~~~~~~~~~~"
        "~~~~~~~~~~~~~~~~"
        "  ~~~~     ~~~~~"
        " g           g ~"
        "        g       "
        "    T      R    "
        "     g          "
        "       P    g   "
        "   g      T     "
        "                "
        "     R      g   "
        "  g             "
        "        g       "
        "       T     g  "
        "           g    "
        "x    g       R  ";

CyberCraft::CyberCraft(RenderContext& renderContext):
        m_renderContext(renderContext)
{
    texture = renderContext.loadTexture("../data/tileset.png");

    world.forEach([this](int x, int y, const BlocInfo*& bloc){
        char tile = gameMap[y*16+x];
        if(tile == 'T'){
            bloc = &getBlocInfo("Tree");
        }else if(tile == '~'){
            bloc = &getBlocInfo("Water");
        }else if(tile == 'R') {
            bloc = &getBlocInfo("Stone");
        }else if(tile == 'g'){
            bloc = &getBlocInfo("LongGrass");
        }else if(tile == ' ') {
            bloc = &getBlocInfo("Grass");
        }else if(tile == 'P'){
            player.pos.x = x;
            player.pos.y = y;
            bloc = &getBlocInfo("Grass");
        }
    });
}

void CyberCraft::update() {
    movePlayer(player.pos, player.player, world);
}

void CyberCraft::draw() {

    world.forEach([this](int x, int y, const BlocInfo* bloc){
        if(!bloc){
            return;
        }
        math::Vector2f pos{static_cast<float>(x), static_cast<float>(y)};
        drawSprite(m_renderContext, texture, pos, bloc->sprite);
    });

    drawSprite(m_renderContext, texture, player.pos, player.sprite);
}

