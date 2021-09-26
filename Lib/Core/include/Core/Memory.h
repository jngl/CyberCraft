//
// Created by jngl on 22/08/2021.
//

#ifndef CYBERCRAFT_MEMORY_H
#define CYBERCRAFT_MEMORY_H

#include "Common.h"

#include <optional>

namespace cc{
    class ByteArray
    {
    private:
        Uint8* m_data = nullptr;
        Uint32 m_size = 0;

    public:
        ByteArray();
        ByteArray(Uint8* copyFrom, Uint32 size);
        explicit ByteArray(Uint32 size);
        ByteArray(const ByteArray&) = delete;
        ByteArray(ByteArray&& moveFrom) noexcept;
        ~ByteArray();

        void clear();
        void copy(Uint8* copyFrom, Uint32 size);
        void copy(void* copyFrom, Uint32 size);

        ByteArray& operator=(const ByteArray&) = delete;
        ByteArray& operator=(ByteArray&&);

        [[nodiscard]] Uint32 size() const;
        [[nodiscard]] const Uint8* data() const;
        [[nodiscard]] Uint8* data();

        static std::optional<ByteArray> loadFromFile(std::string_view filename);
    };
}

#endif //CYBERCRAFT_MEMORY_H
