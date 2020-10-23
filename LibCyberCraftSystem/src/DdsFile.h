//
// Created by jngl on 10/10/2020.
//

#ifndef CYBERCRAFT_DDSFILE_H
#define CYBERCRAFT_DDSFILE_H

#include "System/Common.h"

#include "System/GraphicsData.h"

#include <vector>

namespace cc::System {
    void readDdsFileType(std::fstream& file);
    void readDdsHeader(std::fstream& file, unsigned int& height, unsigned int& width, unsigned int& fourCC, unsigned int& mipMapCount);
    TextureData readDdsFile(std::string_view filename);

    class DdsFile {
    private:
        TextureData m_data;

    public:
        explicit DdsFile(std::string_view filename);

        [[nodiscard]] unsigned int getFormat() const;

        [[nodiscard]] unsigned int getMipMapCount() const;

        [[nodiscard]] const TextureMipMap& getMipMap(unsigned int index);
    };
}

#endif //CYBERCRAFT_DDSFILE_H
