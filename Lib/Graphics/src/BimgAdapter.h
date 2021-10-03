//
// Created by jngl on 28/08/2021.
//

#ifndef CYBERCRAFT_BIMGADAPTER_H
#define CYBERCRAFT_BIMGADAPTER_H

#include <Core/Memory.h>

#include "Enum.h"

namespace cg::Impl
{
    struct ImageContainer
    {
        cc::ByteArray data;

        TextureFormat m_format;
        Orientation m_orientation;

        uint32_t m_size;
        uint32_t m_offset;
        uint32_t m_width;
        uint32_t m_height;
        uint32_t m_depth;
        uint16_t m_numLayers;
        uint8_t  m_numMips;
        bool     m_hasAlpha;
        bool     m_cubeMap;
        bool     m_ktx;
        bool     m_ktxLE;
        bool     m_srgb;
    };

    std::optional<ImageContainer> imageParse(const cc::ByteArray& data);
}



#endif //CYBERCRAFT_BIMGADAPTER_H
