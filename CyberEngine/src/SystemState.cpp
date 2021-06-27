//
// Created by jngl on 05/06/2021.
//

#include "SystemState.h"

SystemState::SystemState() :
m_context(m_window),
m_shaders(m_context)
{
    m_renderer2d = std::make_unique<Renderer2d>();
}

bool SystemState::isRunning() const {
    return m_gameLoader.getGame().isRunning();
}

void SystemState::frame() {
    m_gameLoader.processEvent();
    m_gameLoader.getGame().updateMultiFrameAction();



    m_context.beginFrame();

    m_renderer2d->updateSize(m_window.getSize());

    m_gameLoader.getGame().render(*m_renderer2d);
    m_context.endFrame();
}
