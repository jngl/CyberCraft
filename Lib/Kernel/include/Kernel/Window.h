//
// Created by jngl on 27/06/2020.
//

#ifndef CYBERCRAFTKERNEL_WINDOW_H
#define CYBERCRAFTKERNEL_WINDOW_H

namespace ck {
    class Window {
    public:
        virtual ~Window() = default;

        [[nodiscard]] virtual bool isOpen() const = 0;

        virtual void beginFrame() = 0;

        virtual void endFrame() = 0;
    };
}

#endif //CYBERCRAFT_WINDOW_H
