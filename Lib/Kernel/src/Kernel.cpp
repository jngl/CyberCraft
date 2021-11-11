//
// Created by jngl on 11/11/2021.
//

#include "Kernel/Kernel.h"

#include "Kernel/GraphicsAdapter.h"
#include "Kernel/Window.h"

namespace ck
{
    Kernel::Kernel(GraphicsAdapter &graphicsAdapter) :
    m_graphicsAdapter(graphicsAdapter),
    m_renderer2d(m_graphicsAdapter.getGpuAdapter())
    {
    }

    ck::Renderer2d &Kernel::getRenderer2d() {
        return m_renderer2d;
    }

    void Kernel::beginFrame() {
        auto size = m_graphicsAdapter.getWindow().getSize();
        m_graphicsAdapter.getGpuAdapter().beginFrame(size);

        m_renderer2d.updateSize(size);
    }

    void Kernel::endFrame() {
        m_graphicsAdapter.getGpuAdapter().endFrame();
    }
}
