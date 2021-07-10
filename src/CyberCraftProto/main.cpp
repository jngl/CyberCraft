#include "CyberCraft.h"

#include <CyberCraftSFML/WindowSFML.h>
#include <CyberCraftSFML/RenderContextSFML.h>
#include <Kernel/MainLoop.h>

int main() {
    ccSf::WindowSFML window;
    ccSf::RenderContextSFML renderContext(window.getRenderWindow());
    CyberCraft game(cc::make_ref(renderContext));

    constexpr auto updateTime = std::chrono::milliseconds{16};
	return ck::mainLoop(window, renderContext, game, updateTime);
}
