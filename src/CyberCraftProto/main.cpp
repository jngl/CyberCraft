#include "CyberCraft.h"

#include <CyberCraftSFML/WindowSFML.h>
#include <CyberCraftSFML/RenderContextSFML.h>
#include <Core/MainLoop.h>

int main() {
    ccSf::WindowSFML window;
    ccSf::RenderContextSFML renderContext(window.getRenderWindow());
    CyberCraft game(renderContext);

    constexpr auto updateTime = std::chrono::milliseconds{16};
	return ccCore::mainLoop(window, renderContext, game, updateTime);
}
