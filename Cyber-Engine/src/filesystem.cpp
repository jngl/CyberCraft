#include "filesystem.hpp"

#include <Core/Debug.h>

#include <SDL.h>

namespace filesystem {
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