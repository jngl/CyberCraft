//
// Created by jngl on 05/06/2021.
//

#include "SystemState.h"

SystemState::SystemState() :
m_context(m_window),
m_shaders(m_context)
{}

bool SystemState::isRunning() const {
    return m_gameLoader.getGame().isRunning();
}

void SystemState::frame() {
    m_gameLoader.processEvent();
    m_gameLoader.getGame().updateMultiFrameAction();

    Frame renderer= m_context.beginFrame();
    m_gameLoader.getGame().render(renderer);
}
