//
// Created by jngl on 05/03/2022.
//

#ifndef CYBERCRAFT_DEFAULTPLATFORM_H
#define CYBERCRAFT_DEFAULTPLATFORM_H

#include <Platform.h>
#include <CyberBase/Log.hpp>

#include <memory>

namespace dp::impl {
    class DefaultPlatform;
}

namespace dp
{
    class DefaultPlatform : public cc::Platform
    {
    public:
        explicit DefaultPlatform(std::shared_ptr<cb::Logger> logger);
        DefaultPlatform(const DefaultPlatform&) = delete;
        DefaultPlatform(DefaultPlatform&&) = delete;

        DefaultPlatform& operator=(const DefaultPlatform&) = delete;
        DefaultPlatform& operator=(DefaultPlatform&&) = delete;

        ~DefaultPlatform() override;

        std::vector<cc::Event> getEvents() override;

        void draw() override;

    private:
        std::unique_ptr<impl::DefaultPlatform> m_impl;
    };
}

#endif //CYBERCRAFT_DEFAULTPLATFORM_H
