//
// Created by jngl on 10/10/2020.
//

#ifndef CYBERCRAFT_DDSFILE_H
#define CYBERCRAFT_DDSFILE_H

#include "System/Common.h"

namespace cc::System {
    class DdsFile {
    private:
        unsigned int m_height = 0;
        unsigned int m_width = 0;
        unsigned int m_mipMapCount = 0;
        unsigned int m_fourCC = 0;
        char *m_buffer = nullptr;
    public:
        explicit DdsFile(std::string_view filename);

        ~DdsFile();

        [[nodiscard]] unsigned int getFormat() const;

        [[nodiscard]] unsigned int getWidth() const;

        [[nodiscard]] unsigned int getHeight() const;

        [[nodiscard]] unsigned int getMipMapCount() const;

        [[nodiscard]] const char *getBuffer() const;
    };
}

#endif //CYBERCRAFT_DDSFILE_H
