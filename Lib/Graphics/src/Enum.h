//
// Created by jngl on 26/09/2021.
//

#ifndef CYBERCRAFT_ENUM_H
#define CYBERCRAFT_ENUM_H

namespace cg::Impl
{
    enum class TextureFormat {
        BC1,          //!< DXT1 R5G6B5A1
        BC2,          //!< DXT3 R5G6B5A4
        BC3,          //!< DXT5 R5G6B5A8
        BC4,          //!< LATC1/ATI1 R8
        BC5,          //!< LATC2/ATI2 RG8
        BC6H,         //!< BC6H RGB16F
        BC7,          //!< BC7 RGB 4-7 bits per color channel, 0-8 bits alpha
        ETC1,         //!< ETC1 RGB8
        ETC2,         //!< ETC2 RGB8
        ETC2A,        //!< ETC2 RGBA8
        ETC2A1,       //!< ETC2 RGB8A1
        PTC12,        //!< PVRTC1 RGB 2BPP
        PTC14,        //!< PVRTC1 RGB 4BPP
        PTC12A,       //!< PVRTC1 RGBA 2BPP
        PTC14A,       //!< PVRTC1 RGBA 4BPP
        PTC22,        //!< PVRTC2 RGBA 2BPP
        PTC24,        //!< PVRTC2 RGBA 4BPP
        ATC,          //!< ATC RGB 4BPP
        ATCE,         //!< ATCE RGBA 8 BPP explicit alpha
        ATCI,         //!< ATCI RGBA 8 BPP interpolated alpha
        ASTC4x4,      //!< ASTC 4x4 8.0 BPP
        ASTC5x5,      //!< ASTC 5x5 5.12 BPP
        ASTC6x6,      //!< ASTC 6x6 3.56 BPP
        ASTC8x5,      //!< ASTC 8x5 3.20 BPP
        ASTC8x6,      //!< ASTC 8x6 2.67 BPP
        ASTC10x5,     //!< ASTC 10x5 2.56 BPP

        Unknown,      // Compressed formats above.

        R1,
        A8,
        R8,
        R8I,
        R8U,
        R8S,
        R16,
        R16I,
        R16U,
        R16F,
        R16S,
        R32I,
        R32U,
        R32F,
        RG8,
        RG8I,
        RG8U,
        RG8S,
        RG16,
        RG16I,
        RG16U,
        RG16F,
        RG16S,
        RG32I,
        RG32U,
        RG32F,
        RGB8,
        RGB8I,
        RGB8U,
        RGB8S,
        RGB9E5F,
        BGRA8,
        RGBA8,
        RGBA8I,
        RGBA8U,
        RGBA8S,
        RGBA16,
        RGBA16I,
        RGBA16U,
        RGBA16F,
        RGBA16S,
        RGBA32I,
        RGBA32U,
        RGBA32F,
        R5G6B5,
        RGBA4,
        RGB5A1,
        RGB10A2,
        RG11B10F,

        UnknownDepth, // Depth formats below.

        D16,
        D24,
        D24S8,
        D32,
        D16F,
        D24F,
        D32F,
        D0S8,

        Count
    };

    enum class Orientation
    {
        R0,
        R90,
        R180,
        R270,
        HFlip,
        HFlipR90,
        HFlipR270,
        VFlip,

        Count
    };

    enum class UniformType
    {
        Sampler, //!< Sampler.

        Vec4,    //!< 4 floats vector.
        Mat3,    //!< 3x3 matrix.
        Mat4,    //!< 4x4 matrix.

        Count
    };
}

#endif //CYBERCRAFT_ENUM_H
