#include "Core/Update.h"

#include "Game.h"

#include <CyberCraftSFML/WindowSFML.h>

int main() {

    WindowSFML win;
    FixStepUpdater updater(std::chrono::milliseconds{33});

    Game game(win.getGraphicsContext());

	while (win.isOpen()) {
	    win.beginFrame();

	    game.draw();

	    updater.update([&game](){
	        game.update();
	    });

		win.endFrame();
	}

	return 0;
}
