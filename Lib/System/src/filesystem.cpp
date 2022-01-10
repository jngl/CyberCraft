#include "System/filesystem.hpp"

#include <SDL.h>

namespace cs {
    std::string getBaseDirectory() {
        return SDL_GetBasePath();
    }

    std::string getGameDirectory() {
        return "data";
    }

    std::string getPathSeparator() {
#ifdef _WIN32
        return "\\";
#else
        return "/";
#endif
    }
}
