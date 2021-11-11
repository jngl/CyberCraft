//
// Created by jngl on 19/09/2020.
//

#include <Kernel/MainLoop.h>

#include <Kernel/Game.h>
#include <Ports/Window.h>
#include <Kernel/Engine2D.h>
#include <Kernel/Update.h>

namespace ck {
    [[maybe_unused]] int mainLoop(cp::Window &window, RenderContext2D&, Game &game, std::chrono::milliseconds updateTime) {
        FixStepUpdater updater(updateTime);

        while (window.isOpen()) {
            window.beginFrame();

            game.draw();

            updater.update([&game]() {
                game.update();
            });

            window.endFrame();
        }

        return 0;
    }
}
