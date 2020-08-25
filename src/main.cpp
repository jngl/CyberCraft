#include "Core/Window.h"
#include "Core/Update.h"

#include "Game.h"

int main() {
    Window win;
    FixStepUpdater updater(sf::milliseconds(33));

    Game game;

	while (win.isOpen()) {
	    win.beginFrame();

	    game.draw(win);

	    updater.update([&game](){
	        game.update();
	    });

		win.endFrame();
	}

	return 0;
}
