//
// Created by jngl on 05/06/2021.
//

#include "SystemState.h"

bool SystemState::isRunning() const {
    return m_gameLoader.getGame().isRunning();
}

void SystemState::frame() {
    m_graphics.processEvent(*this, *this);
    m_gameLoader.getGame().updateMultiFrameAction();

    std::unique_ptr<ck::Frame> frame = m_graphics.createFrame();

    m_gameLoader.getGame().render( frame->getColoredRectangleDrawer());
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
