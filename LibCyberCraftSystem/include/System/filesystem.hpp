#pragma once

#include <fstream>
#include <string>

namespace cc::System {
    std::string getBaseDirectory();

    std::string getGameDirectory();

    std::string getPathSeparator();
}
