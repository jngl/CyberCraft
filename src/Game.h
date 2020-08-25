//
// Created by jngl on 18/08/2020.
//

#ifndef CYBERCRAFT_GAME_H
#define CYBERCRAFT_GAME_H

#include "Game/Component.h"
#include "Core/Window.h"
#include "Game/Bloc.h"
#include "Game/World.h"

struct Player {
    component::Sprite sprite;
    component::Player player;
    sf::Vector2f pos;
};

class Game {
public:
    Game();

    void update();
    void draw(Window& win);

private:

    Player player{
            component::Sprite {
                    sf::Vector2i {24,0},
                    sf::Color(255,192,0),
                    sf::Color(0,0,0,0)
            },
            component::Player{0},
            sf::Vector2f {3,2}
    };

    World world;
    sf::Texture texture;
};


#endif //CYBERCRAFT_GAME_H
