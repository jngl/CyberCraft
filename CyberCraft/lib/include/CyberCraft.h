//
// Created by jngl on 05/03/2022.
//

#ifndef CYBERCRAFT_CYBERCRAFT_H
#define CYBERCRAFT_CYBERCRAFT_H

#include <CyberBase/Log.hpp>

#include "Platform.h"

#include <memory>

namespace cc
{
    class CyberCraft final{
    public:
        explicit CyberCraft(std::shared_ptr<cb::Logger> logger, std::unique_ptr<cc::Platform> platform);
        CyberCraft(const CyberCraft&) = delete;
        CyberCraft(CyberCraft&&) = delete;

        const CyberCraft& operator=(const CyberCraft&) = delete;
        const CyberCraft& operator=(CyberCraft&&) = delete;

        ~CyberCraft();

        int run();

    private:
        std::shared_ptr<cb::Logger> m_logger;
        std::unique_ptr<cc::Platform> m_platform;
    };
}



#endif //CYBERCRAFT_CYBERCRAFT_H
