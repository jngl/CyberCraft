//
// Created by jngl on 05/03/2022.
//

#include "CyberCraft.h"

namespace cc {
    CyberCraft::CyberCraft(std::shared_ptr<cb::Logger> logger,
                           std::unique_ptr<cc::Platform> platform):
    m_logger(std::move(logger)),
    m_platform(std::move(platform))
    {
        CB_INFO(m_logger, "CyberCraft", "Construction end");
    }

    CyberCraft::~CyberCraft() {
        CB_INFO(m_logger, "CyberCraft", "Destruction start");
    }

    int CyberCraft::run() {
        bool running = true;
        std::vector<cc::Event> events;
        while(running)
        {
            events = m_platform->getEvents();
            for(cc::Event event: events)
            {
                if(const cc::QuitEvent* quit = std::get_if<cc::QuitEvent>(&event)){
                    running = false;
                }

            }
            events.clear();
            m_platform->draw();
        }
        return 0;
    }
}

