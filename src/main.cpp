#include "Core/Window.h"
#include "Core/Update.h"

int main() {
    Window win;
    Scene scene;
    FixStepUpdater updater(sf::milliseconds(33));


	while (win.isOpen()) {
	    win.beginFrame();
	    updater.update(scene);
		win.endFrame();
	}

	return 0;
}
