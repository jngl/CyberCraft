//
// Created by jngl on 05/06/2021.
//

#include "SystemState.h"

#include <Kernel/Window.h>
#include <Kernel/GpuAdapter.h>

SystemState::SystemState() : m_graphicsAdapter(cg::createGraphicsAdapter()), m_renderer2d(m_graphicsAdapter->getGpuAdapter())
{
}

bool SystemState::isRunning() const {
    return m_gameLoader.getGame().isRunning();
}

void SystemState::frame() {
    m_graphicsAdapter->getWindow().processEvent(*this, *this);
    m_gameLoader.getGame().updateMultiFrameAction();

    auto size = m_graphicsAdapter->getWindow().getSize();
    m_graphicsAdapter->getGpuAdapter().beginFrame(size);


    m_renderer2d.updateSize(size);

    m_gameLoader.getGame().render(m_renderer2d);

    m_graphicsAdapter->getGpuAdapter().endFrame();
}

void SystemState::onKeyUp(ck::Key key) {
    m_gameLoader.getGame().processKeyUp(key);
}

void SystemState::onKeyDown(ck::Key key) {
    if(key == ck::Key::F5){
        m_gameLoader.reload();
    }

    m_gameLoader.getGame().processKeyDown(key);
}

void SystemState::onExit() {
    m_gameLoader.getGame().exit();
}

