//
// Created by jngl on 18/08/2020.
//

#include "Game.h"

#include "Game/System.h"

Game::Game() {
    texture.loadFromFile("../data/tiles.png");

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

void Game::draw(Window &win) {

    world.forEach([this, &win](int x, int y, Bloc bloc){
        const BlocInfo &blocInfo = getBlocInfo(bloc);
        sf::Vector2f pos{static_cast<float>(x), static_cast<float>(y)};
        drawSprite(win, texture, pos, blocInfo.sprite);
    });

    drawSprite(win, texture, player.pos, player.sprite);
}

