#include <CyberCraft.h>

#include <CyberBase/Log.hpp>
#include <memory>

#include <DefaultPlatform.h>

int main()
{
    auto logger = std::make_shared<cb::MultiLogger>();
    logger->addOutput(std::make_unique<cb::FileLogger>("log.csv"));
    logger->addOutput(std::make_unique<cb::ConsoleLogger>());

    auto platform = std::make_unique<dp::DefaultPlatform>(logger);

    cc::CyberCraft cyberCraft(logger, std::move(platform));

    return cyberCraft.run();
}
