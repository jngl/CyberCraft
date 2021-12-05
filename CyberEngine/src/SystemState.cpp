//
// Created by jngl on 05/06/2021.
//

#include "SystemState.h"

#include <Ports/Window.h>

SystemState::SystemState() : m_graphicsAdapter(cg::createGraphicsAdapter()), m_renderer2d(m_graphicsAdapter->getGpuAdapter())
{
}

bool SystemState::isRunning() const {
    return m_gameLoader.getGame().isRunning();
}

void SystemState::frame() {
    auto size = m_graphicsAdapter->getWindow().getSize();
    m_graphicsAdapter->getGpuAdapter().beginFrame(size);

    m_renderer2d.updateSize(size);

    m_gameLoader.getGame().updateMultiFrameAction();

    m_gameLoader.getGame().render(m_renderer2d);

    m_graphicsAdapter->getGpuAdapter().endFrame();
}

//void SystemState::onKeyUp(cp::Key key) {
//    m_gameLoader.getGame().processKeyUp(key);
//}
//
//void SystemState::onKeyDown(cp::Key key) {
//    if(key == cp::Key::F5){
//        m_gameLoader.reload();
//    }
//
//    m_gameLoader.getGame().processKeyDown(key);
//}


