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
        DDS_header header = {0};

        std::string filename2 = getBaseDirectory() +
                                getGameDirectory() +
                                getPathSeparator() +
                                std::string(filename);

        //open file
        std::fstream file(filename2, std::fstream::in | std::fstream::binary);
        ccCore::check("Texture", file.is_open(), "error with dds file : \"", filename2, "\"");

        // check file type
        char fileCode[4];
        file.read(fileCode, 4);
        if (strncmp(fileCode, "DDS ", 4) != 0) {
            file.close();
            ccCore::check("Texture", false, "error in dds file");
        }

        /* récupère la description de la surface */
        file.read(header.data, sizeof(DDS_header));

        m_height = header.dwHeight;
        m_width = header.dwWidth;
        unsigned int linearSize = header.dwPitchOrLinearSize;
        m_mipMapCount = header.dwMipMapCount;
        m_fourCC = header.sPixelFormat.dwFourCC;


        unsigned int bufferSize;
        /* quelle va être la taille des données incluant les MIP maps ? */
        bufferSize = m_mipMapCount > 1 ? linearSize * 2 : linearSize;
        m_buffer = new char[bufferSize];
        file.read(m_buffer, bufferSize);
        /* fermer le pointeur de fichier */
        file.close();
    }

    DdsFile::~DdsFile() {
        delete m_buffer;
    }

    unsigned int DdsFile::getFormat() const {
        switch (m_fourCC) {
            case FOURCC_DXT1:
                return GL_COMPRESSED_RGBA_S3TC_DXT1_EXT;
            case FOURCC_DXT3:
                return GL_COMPRESSED_RGBA_S3TC_DXT3_EXT;
            case FOURCC_DXT5:
                return GL_COMPRESSED_RGBA_S3TC_DXT5_EXT;
            default:
                ccCore::check("Graphics", false, "invalid dds format");
                return 0;
        }
    }

    unsigned int DdsFile::getWidth() const { return m_width; }

    unsigned int DdsFile::getHeight() const { return m_height; }

    unsigned int DdsFile::getMipMapCount() const { return m_mipMapCount; }

    const char *DdsFile::getBuffer() const { return m_buffer; }
}
