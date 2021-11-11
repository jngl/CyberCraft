#include "CyberCraft.h"

#include <Graphics/Graphics.h>

#include <Kernel/MainLoop.h>
#include <Kernel/Renderer2d.h>
#include <Kernel/Kernel.h>

int main() {
    auto graphics = cg::createGraphicsAdapter();
    ck::Kernel kernel(*graphics);

    // TODO
//    CyberCraft game(renderer2D, graphics->getWindow());
//
//    constexpr auto updateTime = std::chrono::milliseconds{16};
//	return ck::mainLoop(graphics->getWindow(), renderer2D, game, updateTime);
}
