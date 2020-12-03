//
// Created by jngl on 17/10/2020.
//

#ifndef CYBERCRAFT_GRAPHICSDATA_H
#define CYBERCRAFT_GRAPHICSDATA_H

#include <Core/Math.h>

#include <vector>

namespace cs {
    enum class TextureFormat{
        DXT1,
        DXT3,
        DXT5
    };

    struct TextureMipMap{
        std::vector<char> data;
        cc::Vector2i size;
    };

    struct TextureData{
        TextureFormat format;
        std::vector<TextureMipMap> mipmaps;
    };
}

#endif //CYBERCRAFT_GRAPHICSDATA_H
