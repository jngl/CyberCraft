//
// Created by jngl on 18/03/2022.
//

#include "DefaultPlatformImpl.h"
#include "CyberBase/Log.hpp"

namespace dp::impl
{
    DefaultPlatform::DefaultPlatform(std::shared_ptr<cb::Logger> logger):
            m_logger(std::move(logger)),
            m_context(m_window)
    {
        CB_INFO(m_logger, "DefaultPlatform", "Construction end");
    }

    DefaultPlatform::~DefaultPlatform() {
        CB_INFO(m_logger, "DefaultPlatform", "Destruction start");
    }

    std::vector<cc::Event> DefaultPlatform:: getEvents()
    {
        return m_window.getEvents();
    }

    void DefaultPlatform::draw() {
        m_context.draw(m_window.getSize());
    }
}

