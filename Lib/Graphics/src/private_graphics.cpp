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

    void Common::startFrame() {
        auto size = m_window.getSize();
        m_bgfxAdapter->beginFrame(size);
        m_renderer2d.updateSize(size);
    }

    void Common::endFrame() {
        m_bgfxAdapter->endFrame();
    }

    ck::Renderer2d &Common::getRenderer2d() {
        return m_renderer2d;
    }

    void Common::processEvent(ck::ExitListener &exitListener, ck::KeyListener &keyListener) {
        m_window.processEvent(exitListener, keyListener);
    }

    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    GraphicsImpl::GraphicsImpl()
    {
    }

    void GraphicsImpl::processEvent(ck::ExitListener &exitListener, ck::KeyListener &keyListener) {
        m_common.processEvent(exitListener, keyListener);
    }

    std::unique_ptr<Frame> GraphicsImpl::createFrame() {
        return std::make_unique<Impl::Frame>(m_common);
    }

    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    Frame::Frame(Common &common):
            m_common(&common)
    {
        m_common->startFrame();
    }

    ck::ColoredRectangleDrawer &Frame::getColoredRectangleDrawer() {
        return m_common->getRenderer2d();
    }

    Frame::~Frame() {
        if(m_common != nullptr){
            m_common->endFrame();
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
}