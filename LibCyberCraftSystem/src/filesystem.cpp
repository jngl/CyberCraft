#include "System/filesystem.hpp"

#include <Core/Debug.h>

#include <SDL.h>

namespace cc::System {
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
