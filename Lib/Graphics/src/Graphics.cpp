//
// Created by jngl on 10/07/2021.
//

#include "Graphics/Graphics.h"

#include "private_Graphics.h"

namespace cg{
    Graphics::Graphics()
    {
        m_data = new Impl::GraphicsImpl;
    }

    Graphics::~Graphics() {
        delete m_data;
    }

    std::unique_ptr<ck::Frame> Graphics::createFrame() {
        return m_data->createFrame();
    }

    void Graphics::processEvent(ck::ExitListener& exitListener, ck::KeyListener &keyListener) {
        m_data->processEvent(exitListener, keyListener);
    }
}
