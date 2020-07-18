#include "Core/Window.h"

int main() {
    Window win;

	while (win.isOpen()) {
	    win.beginFrame();

		//update
		win.update([](){
		});

		win.endFrame();
	}

	return 0;
}
