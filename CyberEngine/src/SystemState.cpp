//
// Created by jngl on 05/06/2021.
//

#include "SystemState.h"

#include <Core/Math.h>

SystemState::SystemState() :
m_graphicsAdapter(cg::createGraphicsAdapter()),
m_gameLoader(*m_graphicsAdapter)
{
}

bool SystemState::isRunning() const {
    return m_graphicsAdapter->getWindow().isOpen();
}

void SystemState::frame() {
    auto size = m_graphicsAdapter->getWindow().getSize();
    m_graphicsAdapter->getGpuAdapter().beginFrame(size);
    m_graphicsAdapter->getWindow().beginFrame();

    if(m_graphicsAdapter->getWindow().isKeyPressed(cp::Key::F5)){
        m_gameLoader.reload(*m_graphicsAdapter);
    }

    m_gameLoader.getGame().update();

    m_gameLoader.getGame().draw();

    m_graphicsAdapter->getGpuAdapter().endFrame();
    m_graphicsAdapter->getWindow().endFrame();
}

//void SystemState::onKeyUp(cp::Key key) {
//    m_gameLoader.getGame().processKeyUp(key);
//}
//
//void SystemState::onKeyDown(cp::Key key) {

//
//    m_gameLoader.getGame().processKeyDown(key);
//}


