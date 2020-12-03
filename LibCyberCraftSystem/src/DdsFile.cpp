//
// Created by jngl on 10/10/2020.
//

#include "System/DdsFile.h"

#include "System/filesystem.hpp"
#include "Core/Debug.h"

#include <cstring>
#include <glad/glad.h>

namespace cc::System {
    /**********************************************************************************
     * Definition
     *********************************************************************************/
    constexpr size_t dwReserved1Size = 11;

    struct DDS_header {
        //uint32_t dwMagic;
        uint32_t dwSize = 0;
        uint32_t dwFlags = 0;
        uint32_t dwHeight = 0;
        uint32_t dwWidth = 0;
        uint32_t dwPitchOrLinearSize = 0;
        uint32_t dwDepth = 0;
        uint32_t dwMipMapCount = 0;
        std::array<uint32_t, dwReserved1Size> dwReserved1 = {0};

        //  DDPIXELFORMAT
        struct {
            uint32_t dwSize = 0;
            uint32_t dwFlags = 0;
            uint32_t dwFourCC = 0;
            uint32_t dwRGBBitCount = 0;
            uint32_t dwRBitMask = 0;
            uint32_t dwGBitMask = 0;
            uint32_t dwBBitMask = 0;
            uint32_t dwAlphaBitMask = 0;
        } sPixelFormat;

        //  DDCAPS2
        struct {
            uint32_t dwCaps1 = 0;
            uint32_t dwCaps2 = 0;
            uint32_t dwDDSX = 0;
            uint32_t dwReserved = 0;
        } sCaps;

        uint32_t dwReserved2 = 0;
    };

    static constexpr unsigned int FOURCC_DXT1 = 0x31545844;
    static constexpr unsigned int FOURCC_DXT3 = 0x33545844;
    static constexpr unsigned int FOURCC_DXT5 = 0x35545844;

    void readDdsFileType(std::fstream& file);
    void readDdsHeader(std::fstream& file, unsigned int& height, unsigned int& width, unsigned int& fourCC, unsigned int& mipMapCount);

    /**********************************************************************************
     * Implementation
     *********************************************************************************/

    void readDdsFileType(std::fstream &file) {
        std::array<char, 4> fileCode{0,0,0,0};
        file.read(fileCode.data(), fileCode.size());
        cc::check("Texture", std::strncmp(fileCode.data(), "DDS ", fileCode.size()) == 0, "error in dds file");
    }

    void readDdsHeader(std::fstream &file, unsigned int& height, unsigned int& width, unsigned int& fourCC, unsigned int& mipMapCount) {
        DDS_header header;

        file.read(reinterpret_cast<char*>(&header), sizeof(DDS_header));   // NOLINT

        height = header.dwHeight;
        width = header.dwWidth;
        fourCC = header.sPixelFormat.dwFourCC;
        mipMapCount = header.dwMipMapCount;
    }

    TextureData readDdsFile(std::string_view filename) {
        TextureData data;

        std::string filename2 = getBaseDirectory() +
                                getGameDirectory() +
                                getPathSeparator() +
                                std::string(filename);

        //open file
        std::fstream file(std::string(filename2), std::fstream::in | std::fstream::binary);
        cc::check("Texture", file.is_open(), "error with dds file : \"", filename, "\"");

        readDdsFileType(file);

        unsigned int width = 0;
        unsigned int height = 0;
        unsigned int fourCC = 0;
        unsigned int mipMapCount = 0;

        readDdsHeader(file, height, width, fourCC, mipMapCount);

        switch (fourCC) {
            case FOURCC_DXT1:
                data.format = TextureFormat::DXT1;
                break;
            case FOURCC_DXT3:
                data.format = TextureFormat::DXT3;
                break;
            case FOURCC_DXT5:
                data.format = TextureFormat::DXT5;
                break;
            default:
                cc::check("Graphics", false, "invalid dds format");
                break;
        }
        data.mipmaps.resize(mipMapCount);

        constexpr int blockSizeDxt1 = 8;
        constexpr int blockSizeDxt35 = 16;

        unsigned int blockSize = (data.format == TextureFormat::DXT1) ? blockSizeDxt1 : blockSizeDxt35;
        for(TextureMipMap& mipMap: data.mipmaps){
            mipMap.size.set(width, height);
            mipMap.data.resize(((width + 3) / 4) * ((height + 3) / 4) * blockSize);
            file.read(mipMap.data.data(), mipMap.data.size());
            width /= 2;
            height /= 2;
        }

        return data;
    }
}
