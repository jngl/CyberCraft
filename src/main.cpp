#include "Core/Window.h"
#include "Core/Update.h"

#include "Game/Component.h"
#include "Game/System.h"

int main() {
    Window win;
    Scene scene;
    FixStepUpdater updater(sf::milliseconds(33));

    sf::Texture texture;
    texture.loadFromFile("../data/tiles.png");

    Entity e = scene.create();
    SpriteComponent& sprite = scene.emplace<SpriteComponent>(e);
    sprite.sprite.setTexture(texture);

	while (win.isOpen()) {
	    win.beginFrame();

        drawSprite(scene, win);

	    updater.update([](){
	    });

		win.endFrame();
	}

	return 0;
}
