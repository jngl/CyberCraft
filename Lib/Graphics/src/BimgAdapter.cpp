//
// Created by jngl on 28/08/2021.
//

#include "BimgAdapter.h"

#include <bimg/decode.h>

#include <bx/allocator.h>
#include <bx/error.h>

namespace cg::Impl
{
    TextureFormat convTextureFormat(bimg::TextureFormat::Enum format){
        switch (format) {
            case bimg::TextureFormat::BC1:
                return TextureFormat::BC1;
            case bimg::TextureFormat::BC2:
                return TextureFormat::BC2;
            case bimg::TextureFormat::BC3:
                return TextureFormat::BC3;
            case bimg::TextureFormat::BC4:
                return TextureFormat::BC4;
            case bimg::TextureFormat::BC5:
                return TextureFormat::BC5;
            case bimg::TextureFormat::BC6H:
                return TextureFormat::BC6H;
            case bimg::TextureFormat::BC7:
                return TextureFormat::BC7;
            case bimg::TextureFormat::ETC1:
                return TextureFormat::ETC1;
            case bimg::TextureFormat::ETC2:
                return TextureFormat::ETC2;
            case bimg::TextureFormat::ETC2A:
                return TextureFormat::ETC2A;
            case bimg::TextureFormat::ETC2A1:
                return TextureFormat::ETC2A1;
            case bimg::TextureFormat::PTC12:
                return TextureFormat::PTC12;
            case bimg::TextureFormat::PTC14:
                return TextureFormat::PTC14;
            case bimg::TextureFormat::PTC12A:
                return TextureFormat::PTC12A;
            case bimg::TextureFormat::PTC14A:
                return TextureFormat::PTC14A;
            case bimg::TextureFormat::PTC22:
                return TextureFormat::PTC22;
            case bimg::TextureFormat::PTC24:
                return TextureFormat::PTC24;
            case bimg::TextureFormat::ATC:
                return TextureFormat::ATC;
            case bimg::TextureFormat::ATCE:
                return TextureFormat::ATCE;
            case bimg::TextureFormat::ATCI:
                return TextureFormat::ATCI;
            case bimg::TextureFormat::ASTC4x4:
                return TextureFormat::ASTC4x4;
            case bimg::TextureFormat::ASTC5x5:
                return TextureFormat::ASTC5x5;
            case bimg::TextureFormat::ASTC6x6:
                return TextureFormat::ASTC6x6;
            case bimg::TextureFormat::ASTC8x5:
                return TextureFormat::ASTC8x5;
            case bimg::TextureFormat::ASTC8x6:
                return TextureFormat::ASTC8x6;
            case bimg::TextureFormat::ASTC10x5:
                return TextureFormat::ASTC10x5;
            case bimg::TextureFormat::R1:
                return TextureFormat::R1;
            case bimg::TextureFormat::A8:
                return TextureFormat::A8;
            case bimg::TextureFormat::R8:
                return TextureFormat::R8;
            case bimg::TextureFormat::R8I:
                return TextureFormat::R8I;
            case bimg::TextureFormat::R8U:
                return TextureFormat::R8U;
            case bimg::TextureFormat::R8S:
                return TextureFormat::R8S;
            case bimg::TextureFormat::R16:
                return TextureFormat::R16;
            case bimg::TextureFormat::R16I:
                return TextureFormat::R16I;
            case bimg::TextureFormat::R16U:
                return TextureFormat::R16U;
            case bimg::TextureFormat::R16F:
                return TextureFormat::R16F;
            case bimg::TextureFormat::R16S:
                return TextureFormat::R16S;
            case bimg::TextureFormat::R32I:
                return TextureFormat::R32I;
            case bimg::TextureFormat::R32U:
                return TextureFormat::R32U;
            case bimg::TextureFormat::R32F:
                return TextureFormat::R32F;
            case bimg::TextureFormat::RG8:
                return TextureFormat::RG8;
            case bimg::TextureFormat::RG8I:
                return TextureFormat::RG8I;
            case bimg::TextureFormat::RG8U:
                return TextureFormat::RG8U;
            case bimg::TextureFormat::RG8S:
                return TextureFormat::RG8S;
            case bimg::TextureFormat::RG16:
                return TextureFormat::RG16;
            case bimg::TextureFormat::RG16I:
                return TextureFormat::RG16I;
            case bimg::TextureFormat::RG16U:
                return TextureFormat::RG16U;
            case bimg::TextureFormat::RG16F:
                return TextureFormat::RG16F;
            case bimg::TextureFormat::RG16S:
                return TextureFormat::RG16S;
            case bimg::TextureFormat::RG32I:
                return TextureFormat::RG32I;
            case bimg::TextureFormat::RG32U:
                return TextureFormat::RG32U;
            case bimg::TextureFormat::RG32F:
                return TextureFormat::RG32F;
            case bimg::TextureFormat::RGB8:
                return TextureFormat::RGB8;
            case bimg::TextureFormat::RGB8I:
                return TextureFormat::RGB8I;
            case bimg::TextureFormat::RGB8U:
                return TextureFormat::RGB8U;
            case bimg::TextureFormat::RGB8S:
                return TextureFormat::RGB8S;
            case bimg::TextureFormat::RGB9E5F:
                return TextureFormat::RGB9E5F;
            case bimg::TextureFormat::BGRA8:
                return TextureFormat::BGRA8;
            case bimg::TextureFormat::RGBA8:
                return TextureFormat::RGBA8;
            case bimg::TextureFormat::RGBA8I:
                return TextureFormat::RGBA8I;
            case bimg::TextureFormat::RGBA8U:
                return TextureFormat::RGBA8U;
            case bimg::TextureFormat::RGBA8S:
                return TextureFormat::RGBA8S;
            case bimg::TextureFormat::RGBA16:
                return TextureFormat::RGBA16;
            case bimg::TextureFormat::RGBA16I:
                return TextureFormat::RGBA16I;
            case bimg::TextureFormat::RGBA16U:
                return TextureFormat::RGBA16U;
            case bimg::TextureFormat::RGBA16F:
                return TextureFormat::RGBA16F;
            case bimg::TextureFormat::RGBA16S:
                return TextureFormat::RGBA16S;
            case bimg::TextureFormat::RGBA32I:
                return TextureFormat::RGBA32I;
            case bimg::TextureFormat::RGBA32U:
                return TextureFormat::RGBA32U;
            case bimg::TextureFormat::RGBA32F:
                return TextureFormat::RGBA32F;
            case bimg::TextureFormat::R5G6B5:
                return TextureFormat::R5G6B5;
            case bimg::TextureFormat::RGBA4:
                return TextureFormat::RGBA4;
            case bimg::TextureFormat::RGB5A1:
                return TextureFormat::RGB5A1;
            case bimg::TextureFormat::RGB10A2:
                return TextureFormat::RGB10A2;
            case bimg::TextureFormat::RG11B10F:
                return TextureFormat::RG11B10F;
            case bimg::TextureFormat::D16:
                return TextureFormat::D16;
            case bimg::TextureFormat::D24:
                return TextureFormat::D24;
            case bimg::TextureFormat::D24S8:
                return TextureFormat::D24S8;
            case bimg::TextureFormat::D32:
                return TextureFormat::D32;
            case bimg::TextureFormat::D16F:
                return TextureFormat::D16F;
            case bimg::TextureFormat::D24F:
                return TextureFormat::D24F;
            case bimg::TextureFormat::D32F:
                return TextureFormat::D32F;
            case bimg::TextureFormat::D0S8:
                return TextureFormat::D0S8;
            default:
                return TextureFormat::Unknown;
        }
    }

    Orientation convOrientation(bimg::Orientation::Enum value){
        switch (value) {
            case bimg::Orientation::R0:
                return Orientation::R0;
            case bimg::Orientation::R90:
                return Orientation::R90;
            case bimg::Orientation::R180:
                return Orientation::R180;
            case bimg::Orientation::R270:
                return Orientation::R270;
            case bimg::Orientation::HFlip:
                return Orientation::HFlip;
            case bimg::Orientation::HFlipR90:
                return Orientation::HFlipR90;
            case bimg::Orientation::HFlipR270:
                return Orientation::HFlipR270;
            case bimg::Orientation::VFlip:
                return Orientation::VFlip;
            default:
                return Orientation::Count;
        }
    }

    bx::DefaultAllocator s_allocator;

    std::optional<ImageContainer> imageParse(const cc::ByteArray& data){
        const void* dataPtr = data.data();
        uint32_t size = data.size();
        bimg::TextureFormat::Enum bimgFormat = bimg::TextureFormat::Count;
        bx::Error err;

        bimg::ImageContainer* bimgContainer = bimg::imageParse(&s_allocator, dataPtr, size, bimgFormat, &err);

        if(!err.isOk()){
            return {};
        }

        if(bimgContainer == nullptr){
            return {};
        }

        ImageContainer image;
        image.data.copy(bimgContainer->m_data, bimgContainer->m_size);

        image.m_format = convTextureFormat(bimgContainer->m_format);
        image.m_orientation = convOrientation(bimgContainer->m_orientation);

        image.m_offset = bimgContainer->m_offset;
        image.m_width = bimgContainer->m_width;
        image.m_height = bimgContainer->m_height;
        image.m_depth = bimgContainer->m_depth;
        image.m_numLayers = bimgContainer->m_numLayers;
        image.m_numMips = bimgContainer->m_numMips;
        image.m_hasAlpha = bimgContainer->m_hasAlpha;
        image.m_cubeMap = bimgContainer->m_cubeMap;
        image.m_ktx = bimgContainer->m_ktx;
        image.m_ktxLE = bimgContainer->m_ktxLE;
        image.m_srgb = bimgContainer->m_srgb;

        bimg::imageFree(bimgContainer);

        return image;
    }
}
