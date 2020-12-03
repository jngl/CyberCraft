//
// Created by jngl on 10/10/2020.
//

#ifndef CYBERCRAFT_DDSFILE_H
#define CYBERCRAFT_DDSFILE_H

#include "System/Common.h"

#include "System/GraphicsData.h"

#include <vector>

namespace cs {
    TextureData readDdsFile(std::string_view filename);
}

#endif //CYBERCRAFT_DDSFILE_H
