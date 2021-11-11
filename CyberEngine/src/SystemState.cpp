//
// Created by jngl on 05/06/2021.
//

#include "SystemState.h"

#include <Ports/Window.h>

SystemState::SystemState() : m_graphicsAdapter(cg::createGraphicsAdapter()), m_kernel(*m_graphicsAdapter)
{
}

bool SystemState::isRunning() const {
    return m_gameLoader.getGame().isRunning();
}

void SystemState::frame() {
    // TODO
    //m_graphicsAdapter->getWindow().processEvent(*this, *this);
    m_gameLoader.getGame().updateMultiFrameAction();

    m_gameLoader.getGame().render(m_kernel.getRenderer2d());

    m_kernel.nextFrame();
}

void SystemState::onKeyUp(cp::Key key) {
    m_gameLoader.getGame().processKeyUp(key);
}

void SystemState::onKeyDown(cp::Key key) {
    if(key == cp::Key::F5){
        m_gameLoader.reload();
    }

    m_gameLoader.getGame().processKeyDown(key);
}

void SystemState::onExit() {
    m_gameLoader.getGame().exit();
}

