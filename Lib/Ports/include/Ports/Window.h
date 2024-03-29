//
// Created by jngl on 27/06/2020.
//

#ifndef CYBERCRAFTKERNEL_WINDOW_H
#define CYBERCRAFTKERNEL_WINDOW_H

#include "Key.h"

namespace cc
{
    template<class T>
    struct Vector2;

    using Vector2ui = Vector2<unsigned int>;
}

namespace cp {
    class Window {
    public:
        virtual ~Window() = default;

        [[nodiscard]] virtual bool isOpen() const = 0;

        virtual void beginFrame() = 0;

        virtual void endFrame() = 0;

        virtual bool isKeyPressed(Key) = 0;

        [[nodiscard]] virtual cc::Vector2ui getSize() const = 0;
    };
}

#endif //CYBERCRAFT_WINDOW_H
