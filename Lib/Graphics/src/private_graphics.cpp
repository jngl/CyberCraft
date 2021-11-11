//
// Created by jngl on 10/07/2021.
//

#include "private_Graphics.h"

namespace cg::Impl{

    GraphicsAdapter::GraphicsAdapter(): m_bgfxAdapter(createBgfxAdapter(m_window))
    {
    }

    cp::GpuAdapter &GraphicsAdapter::getGpuAdapter() {
        return *m_bgfxAdapter;
    }

    cp::Window &GraphicsAdapter::getWindow() {
        return m_window;
    }
}
