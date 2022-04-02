//
// Created by jngl on 05/03/2022.
//

#include "DefaultPlatform.h"

#include "DefaultPlatformImpl.h"

namespace dp
{
    DefaultPlatform::DefaultPlatform(std::shared_ptr<cb::Logger> logger)
    {
        m_impl = std::make_unique<impl::DefaultPlatform>(logger);
    }

    DefaultPlatform::~DefaultPlatform()
    {
    }

    std::vector<cc::Event> DefaultPlatform::getEvents()  {
        return m_impl->getEvents();
    }

    void DefaultPlatform::draw() {
        m_impl->draw();
    }
}

