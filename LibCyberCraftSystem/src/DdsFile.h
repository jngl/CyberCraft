//
// Created by jngl on 10/10/2020.
//

#ifndef CYBERCRAFT_DDSFILE_H
#define CYBERCRAFT_DDSFILE_H

#include "System/Common.h"

#include <vector>

namespace cc::System {
    class DdsFile {
    public:
        struct MipMap
        {
            unsigned int width = 0;
            unsigned int height = 0;
            std::vector<char> data;
        };

    private:
        unsigned int m_height = 0;
        unsigned int m_width = 0;
        unsigned int m_fourCC = 0;

        std::vector<MipMap> m_mipMaps;

        static void readFileType(std::fstream& file);
        void readHeader(std::fstream& file);
    public:
        explicit DdsFile(std::string_view filename);

        [[nodiscard]] unsigned int getFormat() const;

        [[nodiscard]] unsigned int getWidth() const;

        [[nodiscard]] unsigned int getHeight() const;

        [[nodiscard]] unsigned int getMipMapCount() const;

        [[nodiscard]] const MipMap& getMipMap(unsigned int index);
    };
}

#endif //CYBERCRAFT_DDSFILE_H
