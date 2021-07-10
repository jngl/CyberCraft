//
// Created by jngl on 05/06/2021.
//

#include "SystemState.h"

SystemState::SystemState() :
m_context(m_window),
m_shaders(m_context)
{
    m_renderer2d.setShader(m_shaders.get(m_shaders.getHandleFromFile("simple2d")));
}

bool SystemState::isRunning() const {
    return m_gameLoader.getGame().isRunning();
}

void SystemState::frame() {
    m_gameLoader.processEvent();
    m_gameLoader.getGame().updateMultiFrameAction();

    auto size = m_window.getSize();
    m_context.beginFrame(size);
    m_renderer2d.updateSize(size);

    m_gameLoader.getGame().render(m_renderer2d);

    m_context.endFrame();
}
