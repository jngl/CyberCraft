//
// Created by jngl on 18/08/2020.
//

#include "Game.h"

#include "Game/System.h"

Game::Game(GraphicsContext& graphicsContext):
        m_graphicsContext(graphicsContext)
{
    texture = graphicsContext.loadTexture("../data/tiles.png");

    world.forEach([this](int x, int y, Bloc& bloc){
        if(y<=1){
            bloc = Bloc::Water;
        }else if(y>11 && x>10) {
            bloc = Bloc::Stone;
        }else{
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

