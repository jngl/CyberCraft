#include "CyberCraft.h"

#include <CyberCraftSFML/WindowSFML.h>
#include <CyberCraftSFML/RenderContextSFML.h>
#include <GameEngine.h>

int main() {
    WindowSFML window;
    RenderContextSFML renderContext(window.getRenderWindow());
    CyberCraft game(renderContext);
    GameEngine gameEngine(window, renderContext, game);

	return gameEngine.exec();
}
