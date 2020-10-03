#include "filesystem.hpp"

#include "debugAssert.hpp"

#include <SDL.h>

namespace filesystem
{
  std::string getBaseDirectory(){
    return SDL_GetBasePath();
  }
  
  std::string getGameDirectory(){
    return "data";
  }

  
  std::string getPathSeparator(){
#ifdef _WIN32
    return "\\";
#else
    return "/";
#endif
  }

  // main
  void createFileSystem(){
    debug::log("FileSystem", "construct");
    debug::log("Filesystem", "Data Directory : \"", getBaseDirectory(), getGameDirectory(), "\"");
  }
  
  void destroyFileSystem(){
    debug::log("FileSystem", "destruct");
  }

}
