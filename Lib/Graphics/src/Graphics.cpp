//
// Created by jngl on 10/07/2021.
//

#include "Graphics/Graphics.h"

#include "private_Graphics.h"

namespace cg{
    Graphics::Graphics()
    {
        m_data = new Impl::GraphicsData;
    }

    Graphics::~Graphics() {
        delete m_data;
    }

    std::unique_ptr<ck::Frame> Graphics::createFrame() {
        return std::make_unique<Impl::Frame>(*this);
    }

    void Graphics::processEvent(ck::ExitListener& exitListener, ck::KeyListener &keyListener) {
        SDL_Event event;
        while (SDL_PollEvent(&event) != 0) {
            switch(event.type){
                case SDL_KEYDOWN:
                    keyListener.onKeyDown(Impl::keyFromSdlKey(event.key.keysym.sym));
                    break;
                case SDL_KEYUP:
                    keyListener.onKeyUp(Impl::keyFromSdlKey(event.key.keysym.sym));
                    break;
                case SDL_QUIT:
                    exitListener.onExit();
                    break;
                default:
                    break;
            }
        }
    }
}
