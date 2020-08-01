/*#include "Core/Window.h"
#include "Core/Update.h"

#include "Game/Component.h"
#include "Game/System.h"
*/
#include <array>
#include <memory>
#include <cassert>
#include <iostream>

#include "Core/BTreePlus.h"
/*
void createPlayer(Scene& scene, const sf::Texture& texture){
    Entity e = scene.create();

    SpriteComponent& sprite = scene.emplace<SpriteComponent>(e);
    sprite.texture = &texture;
    sprite.textureIndex.x = 24;
    sprite.textureIndex.y = 0;
    sprite.color = sf::Color::White;

    PositionComponent& pos = scene.emplace<PositionComponent>(e);
    pos.position.x = 10;
    pos.position.y = 10;

    scene.emplace<PlayerComponent>(e);
}

void createWorld(Scene& scene, const sf::Texture& texture){
    Entity e = scene.create();

    SpriteComponent& sprite = scene.emplace<SpriteComponent>(e);
    sprite.texture = &texture;
    sprite.textureIndex.x = 0;
    sprite.textureIndex.y = 1;
    sprite.color = sf::Color::Green;

    PositionComponent& pos = scene.emplace<PositionComponent>(e);
    pos.position.x = 150;
    pos.position.y = 200;

}
*/

int main() {
    BTreePlus<int, std::string, 4> btree;
    btree.debugPrint();

    auto step = [&btree](int i){
        std::cout<<"insert "<<i<<"\n";
        btree.insert(i, std::string("Data")+std::to_string(i));
        btree.debugPrint();
    };
    step(42);
    step(1);
    step(666);
    step(24);
    step(48);
    step(30);
    step(10);
    step(15);

    /*Window win;
    Scene scene;
    FixStepUpdater updater(sf::milliseconds(33));

    sf::Texture texture;
    texture.loadFromFile("../data/tiles.png");

    createPlayer(scene, texture);
    createWorld(scene, texture);

	while (win.isOpen()) {
	    win.beginFrame();

        drawSprite(scene, win);

	    updater.update([&scene](){
	        movePlayer(scene);
	    });

		win.endFrame();
	}*/

	return 0;
}
