#include "CyberCraft.h"

#include <CyberCraftSFML/WindowSFML.h>
#include <CyberCraftSFML/RenderContextSFML.h>
#include <Core/MainLoop.h>

int main() {
    ccSf::WindowSFML window;
    ccSf::RenderContextSFML renderContext(window.getRenderWindow());
    CyberCraft game(renderContext);

	return ccCore::mainLoop(window, renderContext, game, std::chrono::milliseconds{33});
}
