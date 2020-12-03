//
// Created by jngl on 19/09/2020.
//

#include <Core/MainLoop.h>

#include <Core/Game.h>
#include <Core/Window.h>
#include <Core/RenderContext.h>
#include <Core/Update.h>

namespace cc {
    [[maybe_unused]] int mainLoop(Window &window, RenderContext &/*renderContext*/, Game &game, std::chrono::milliseconds updateTime) {
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