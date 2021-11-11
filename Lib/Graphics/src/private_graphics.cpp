//
// Created by jngl on 10/07/2021.
//

#include "private_Graphics.h"

#include <string>
#include <algorithm>

#include <fmt/core.h>

#include "BimgAdapter.h"

#include <Core/Memory.h>

#include <Kernel/GpuBuffer.h>

namespace cg::Impl{



    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    Common::Common():
            m_bgfxAdapter(createBgfxAdapter(m_window)),
            m_renderer2d(*m_bgfxAdapter)
    {
    }

    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    Frame::Frame(Common &common):
            m_common(&common)
    {

        auto size = m_common->m_window.getSize();
        m_common->m_bgfxAdapter->beginFrame(size);
        m_common->m_renderer2d.updateSize(size);
    }

    ck::ColoredRectangleDrawer &Frame::getColoredRectangleDrawer() {
        return m_common->m_renderer2d;
    }

    Frame::~Frame() {
        if(m_common != nullptr){
            m_common->m_bgfxAdapter->endFrame();
        }
    }

    Frame::Frame(Frame && other) noexcept {
        m_common = other.m_common;
        other.m_common = nullptr;
    }

    Frame &Frame::operator=(Frame && other) noexcept {
        m_common = other.m_common;
        other.m_common = nullptr;
        return *this;
    }

    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    std::unique_ptr<ck::Frame> GraphicsAdapter::createFrame() {
        return std::make_unique<Impl::Frame>(m_common);
    }

    void GraphicsAdapter::processEvent(ck::ExitListener &exitListener, ck::KeyListener &keyListener) {
        m_common.m_window.processEvent(exitListener, keyListener);
    }
}