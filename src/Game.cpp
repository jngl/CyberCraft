//
// Created by jngl on 18/08/2020.
//

#include "Game.h"

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

Game::Game(GraphicsContext& graphicsContext):
        m_graphicsContext(graphicsContext)
{
    texture = graphicsContext.loadTexture("../data/tileset.png");

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

void Game::update() {
    movePlayer(player.pos, player.player, world);
}

void Game::draw() {

    world.forEach([this](int x, int y, const BlocInfo* bloc){
        if(!bloc){
            return;
        }
        math::Vector2f pos{static_cast<float>(x), static_cast<float>(y)};
        drawSprite(m_graphicsContext, texture, pos, bloc->sprite);
    });

    drawSprite(m_graphicsContext, texture, player.pos, player.sprite);
}

