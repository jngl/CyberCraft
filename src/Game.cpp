//
// Created by jngl on 18/08/2020.
//

#include "Game.h"

#include "Game/System.h"

const char* gameMap =
        "~~~~~~~~~~~~~~~~"
        "~~~~~~~~~~~~~~~~"
        "  ~~~~     ~~~~~"
        "               ~"
        "                "
        "    T      R    "
        "                "
        "       P        "
        "          T     "
        "                "
        "     R          "
        "                "
        "                "
        "       T        "
        "                "
        "             R  ";

Game::Game(GraphicsContext& graphicsContext):
        m_graphicsContext(graphicsContext)
{
    texture = graphicsContext.loadTexture("../data/tiles.png");

    world.forEach([this](int x, int y, Bloc& bloc){
        char tile = gameMap[y*16+x];
        if(tile == 'T'){
            bloc = Bloc::Tree;
        }else if(tile == '~'){
            bloc = Bloc::Water;
        }else if(tile == 'R') {
            bloc = Bloc::Stone;
        }else{
            if(tile == 'P'){
                player.pos.x = x;
                player.pos.y = y;
            }

            bloc = Bloc::Grass;
        }
    });
}

void Game::update() {
    movePlayer(player.pos, player.player, world);
}

void Game::draw() {

    world.forEach([this](int x, int y, Bloc bloc){
        const BlocInfo &blocInfo = getBlocInfo(bloc);
        math::Vector2f pos{static_cast<float>(x), static_cast<float>(y)};
        drawSprite(m_graphicsContext, texture, pos, blocInfo.sprite);
    });

    drawSprite(m_graphicsContext, texture, player.pos, player.sprite);
}

