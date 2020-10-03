#pragma once

#include <fstream>
#include <string>

namespace filesystem {
  std::string getBaseDirectory();
  std::string getGameDirectory();
  std::string getPathSeparator();

  // main
  void createFileSystem();
  void destroyFileSystem();
}
