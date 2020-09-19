#include "CyberCraft.h"

#include <CyberCraftSFML/WindowSFML.h>
#include <CyberCraftSFML/RenderContextSFML.h>
#include <Core/MainLoop.h>

int main() {
    WindowSFML window;
    RenderContextSFML renderContext(window.getRenderWindow());
    CyberCraft game(renderContext);

	return mainLoop(window, renderContext, game, std::chrono::milliseconds{33});
}
