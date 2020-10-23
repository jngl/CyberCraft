//
// Created by jngl on 10/10/2020.
//

#include "DdsFile.h"

#include "System/filesystem.hpp"
#include "Core/Debug.h"

#include <cstring>
#include <glad/glad.h>

namespace cc::System {
    union DDS_header {
        struct {
            //uint32_t dwMagic;
            uint32_t dwSize;
            uint32_t dwFlags;
            uint32_t dwHeight;
            uint32_t dwWidth;
            uint32_t dwPitchOrLinearSize;
            uint32_t dwDepth;
            uint32_t dwMipMapCount;
            uint32_t dwReserved1[11];

            //  DDPIXELFORMAT
            struct {
                uint32_t dwSize;
                uint32_t dwFlags;
                uint32_t dwFourCC;
                uint32_t dwRGBBitCount;
                uint32_t dwRBitMask;
                uint32_t dwGBitMask;
                uint32_t dwBBitMask;
                uint32_t dwAlphaBitMask;
            } sPixelFormat;

            //  DDCAPS2
            struct {
                uint32_t dwCaps1;
                uint32_t dwCaps2;
                uint32_t dwDDSX;
                uint32_t dwReserved;
            } sCaps;

            uint32_t dwReserved2;
        };
        char data[124];
    };

    static constexpr unsigned int FOURCC_DXT1 = 0x31545844;
    static constexpr unsigned int FOURCC_DXT3 = 0x33545844;
    static constexpr unsigned int FOURCC_DXT5 = 0x35545844;

    DdsFile::DdsFile(std::string_view filename) {
        m_data = readDdsFile(filename);
    }

    unsigned int DdsFile::getFormat() const {
        switch (m_data.format) {
            case TextureFormat::DXT1:
                return GL_COMPRESSED_RGBA_S3TC_DXT1_EXT;
            case TextureFormat::DXT3:
                return GL_COMPRESSED_RGBA_S3TC_DXT3_EXT;
            case TextureFormat::DXT5:
                return GL_COMPRESSED_RGBA_S3TC_DXT5_EXT;
            default:
                ccCore::check("Graphics", false, "invalid dds format");
                return 0;
        }
    }

    unsigned int DdsFile::getMipMapCount() const { return m_data.mipmaps.size(); }

    void readDdsFileType(std::fstream &file) {
        char fileCode[4];
        file.read(fileCode, 4);
        ccCore::check("Texture", strncmp(fileCode, "DDS ", 4) == 0, "error in dds file");
    }

    void readDdsHeader(std::fstream &file, unsigned int& height, unsigned int& width, unsigned int& fourCC, unsigned int& mipMapCount) {
        DDS_header header = {0};

        file.read(header.data, sizeof(DDS_header));

        height = header.dwHeight;
        width = header.dwWidth;
        fourCC = header.sPixelFormat.dwFourCC;
        mipMapCount = header.dwMipMapCount;
    }

    const TextureMipMap &DdsFile::getMipMap(unsigned int index) {
        return m_data.mipmaps.at(index);
    }

    TextureData readDdsFile(std::string_view filename) {
        TextureData data;

        std::string filename2 = getBaseDirectory() +
                                getGameDirectory() +
                                getPathSeparator() +
                                std::string(filename);

        //open file
        std::fstream file(std::string(filename2), std::fstream::in | std::fstream::binary);
        ccCore::check("Texture", file.is_open(), "error with dds file : \"", filename, "\"");

        readDdsFileType(file);

        unsigned int width;
        unsigned int height;
        unsigned int fourCC;
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
                ccCore::check("Graphics", false, "invalid dds format");
                break;
        }
        data.mipmaps.resize(mipMapCount);

        unsigned int blockSize = (data.format == TextureFormat::DXT1) ? 8 : 16;
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
