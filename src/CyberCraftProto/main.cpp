#include "CyberCraft.h"

#include <CyberCraftSFML/WindowSFML.h>
#include <CyberCraftSFML/RenderContextSFML.h>
#include <Kernel/MainLoop.h>

int main() {
    ccSf::WindowSFML window;
    ccSf::RenderContextSFML renderContext(window.getRenderWindow());
    CyberCraft game(cc::make_ref(renderContext));

    constexpr auto updateTime = std::chrono::milliseconds{16};
<<<<<<< HEAD:src/CyberCraftProto/main.cpp
	return ck::mainLoop(window, renderContext, game, updateTime);
=======
	return cc::mainLoop(window, renderContext, game, updateTime);
>>>>>>> b0d8808aab9721dbaa8c9afaf9c8a706f1faee8f:src/main.cpp
}
