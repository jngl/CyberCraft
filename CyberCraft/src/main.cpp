#include <CyberBase/Log.hpp>
#include <memory>

int main()
{
    cb::MultiLogger log;
    log.addOutput(std::make_unique<cb::FileLogger>("log.csv"));
    log.addOutput(std::make_unique<cb::ConsoleLogger>());

    CB_INFO(log, "main", "Test");
}
