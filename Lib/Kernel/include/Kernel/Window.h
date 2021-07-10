//
// Created by jngl on 27/06/2020.
//

#ifndef CYBERCRAFTKERNEL_WINDOW_H
#define CYBERCRAFTKERNEL_WINDOW_H

<<<<<<< HEAD:Lib/Kernel/include/Kernel/Window.h
namespace ck {
=======
namespace cc {
>>>>>>> b0d8808aab9721dbaa8c9afaf9c8a706f1faee8f:LibCyberCraftCore/include/Core/Window.h
    class Window {
    public:
        virtual ~Window() = default;

        [[nodiscard]] virtual bool isOpen() const = 0;

        virtual void beginFrame() = 0;

        virtual void endFrame() = 0;
    };
}

#endif //CYBERCRAFT_WINDOW_H
