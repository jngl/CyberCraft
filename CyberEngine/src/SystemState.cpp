//
// Created by jngl on 05/06/2021.
//

#include "SystemState.h"

SystemState::SystemState()
{
}

bool SystemState::isRunning() const {
    return m_gameLoader.getGame().isRunning();
}

void SystemState::frame() {
    m_gameLoader.processEvent();
    m_gameLoader.getGame().updateMultiFrameAction();

    auto size = m_graphics.getWindowSdl().getSize();
    m_graphics.getContext().beginFrame(size);
    m_graphics.getRenderer2d().updateSize(size);

    m_gameLoader.getGame().render(m_graphics.getRenderer2d());

    m_graphics.getContext().endFrame();
}
