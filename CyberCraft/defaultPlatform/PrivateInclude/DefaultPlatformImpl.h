//
// Created by jngl on 18/03/2022.
//

#ifndef CYBERCRAFT_DEFAULTPLATFORMIMPL_H
#define CYBERCRAFT_DEFAULTPLATFORMIMPL_H

#include "memory"
#include "SdlWindow.h"
#include "BgfxContext.h"

namespace cb
{
    class Logger;
}

namespace dp::impl
{
    class DefaultPlatform final
    {
    public:
        explicit DefaultPlatform(std::shared_ptr<cb::Logger> logger);
        DefaultPlatform(const DefaultPlatform&) = delete;
        DefaultPlatform(DefaultPlatform&&) = delete;

        DefaultPlatform& operator=(const DefaultPlatform&) = delete;
        DefaultPlatform& operator=(DefaultPlatform&&) = delete;

        ~DefaultPlatform();

        std::vector<cc::Event> getEvents();

        void draw();

    private:
        std::shared_ptr<cb::Logger> m_logger;
        SdlWindow m_window;
        BgfxContext m_context;
    };
}


#endif //CYBERCRAFT_DEFAULTPLATFORMIMPL_H
