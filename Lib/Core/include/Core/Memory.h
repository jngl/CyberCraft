//
// Created by jngl on 22/08/2021.
//

#ifndef CYBERCRAFT_MEMORY_H
#define CYBERCRAFT_MEMORY_H

#include "Common.h"

#include <optional>
#include <array>
#include <string_view>

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

        static std::optional<ByteArray> loadFromFile(std::string_view filename);

        template<class T, size_t size>
        static ByteArray copyFromArray(const std::array<T, size>& array){
            return ByteArray(array.data(), array.size() * sizeof(T));
        }
    };

    class ByteArrayView
    {
    private:
        const void* m_data = nullptr;
        Uint32 m_size = 0;

    public:
        ByteArrayView() = default;
        ByteArrayView(const void* refFrom, Uint32 size);
        ByteArrayView(const ByteArray&);
        ByteArrayView(const ByteArrayView&);
        ByteArrayView(ByteArrayView&& moveFrom) noexcept;

        void clear();
        void ref(void* refFrom, Uint32 size);

        ByteArrayView& operator=(const ByteArray&);

        ByteArrayView& operator=(const ByteArrayView&);
        ByteArrayView& operator=(ByteArrayView&&);

        [[nodiscard]] Uint32 size() const;
        [[nodiscard]] const void* data() const;

        template<class T, size_t size>
        static ByteArray fromArray(const std::array<T, size>& array){
            return ByteArray(array.data(), array.size() * sizeof(T));
        }
    };
}

#endif //CYBERCRAFT_MEMORY_H
