//
// Created by jngl on 19/09/2020.
//

#include <Kernel/MainLoop.h>

<<<<<<< HEAD:Lib/Kernel/src/MainLoop.cpp
#include <Kernel/Game.h>
#include <Kernel/Window.h>
#include <Kernel/Engine2D.h>
#include <Kernel/Update.h>

namespace ck {
=======
#include <Core/Game.h>
#include <Core/Window.h>
#include <Core/Engine2D.h>
#include <Core/Update.h>

namespace cc {
>>>>>>> b0d8808aab9721dbaa8c9afaf9c8a706f1faee8f:LibCyberCraftCore/src/Core/MainLoop.cpp
    [[maybe_unused]] int mainLoop(Window &window, RenderContext2D&, Game &game, std::chrono::milliseconds updateTime) {
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