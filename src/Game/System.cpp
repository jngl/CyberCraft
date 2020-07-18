//
// Created by jngl on 18/07/2020.
//

#include "System.h"

#include "Component.h"

void drawSprite(Scene &scene, Window& win) {
    sf::RenderWindow& sfWin = win.getSFMLWindowsRef();

    auto view = scene.view<SpriteComponent>();

    for(auto entity: view){
        auto& sprite = view.get<SpriteComponent>(entity);
        sfWin.draw(sprite.sprite);
    }
}
