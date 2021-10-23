//
// Created by jngl on 22/08/2021.
//

#ifndef CYBERCRAFT_MEMORY_H
#define CYBERCRAFT_MEMORY_H

#include "Common.h"

#include <optional>
#include <array>

namespace cc{
    class ByteArray
    {
    private:
        void* m_data = nullptr;
        Uint32 m_size = 0;

    public:
        ByteArray();
        ByteArray(const void* copyFrom, Uint32 size);
        explicit ByteArray(Uint32 size);
        ByteArray(const ByteArray&);
        ByteArray(ByteArray&& moveFrom) noexcept;
        ~ByteArray();

        void clear();
        void copy(void* copyFrom, Uint32 size);

        ByteArray& operator=(const ByteArray&);
        ByteArray& operator=(ByteArray&&);

        [[nodiscard]] Uint32 size() const;
        [[nodiscard]] const void* data() const;
        [[nodiscard]] void* data();

        static std::optional<ByteArray> loadFromFile(std::string_view filename);

        template<class T, size_t size>
        static ByteArray copyFromArray(const std::array<T, size>& array){
            return ByteArray(array.data(), array.size() * sizeof(T));
        }
    };
}

#endif //CYBERCRAFT_MEMORY_H
