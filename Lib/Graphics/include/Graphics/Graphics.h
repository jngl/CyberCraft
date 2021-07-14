//
// Created by jngl on 10/07/2021.
//

#ifndef CYBERCRAFT_GRAPHICS_H
#define CYBERCRAFT_GRAPHICS_H

#include <Kernel/Graphics.h>

namespace cg{
    class Graphics;

    namespace Impl{
        class GraphicsImpl;
        class Frame;
    }

    class Graphics : ck::Graphics{
    public:
        friend class Impl::Frame;

        Graphics();
        ~Graphics() override;

        std::unique_ptr<ck::Frame> createFrame() override;

        void processEvent(ck::ExitListener& exitListener, ck::KeyListener& keyListener) override;

    private:
        Impl::GraphicsImpl* m_data = nullptr;
    };
}

#endif //CYBERCRAFT_GRAPHICS_H
