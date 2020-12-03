//
// Created by jngl on 03/12/2020.
//

#ifndef CYBERCRAFT_POINTER_H
#define CYBERCRAFT_POINTER_H

#include <exception>

#include "Core/Common.h"

namespace cc {
    class NullPointerException final : std::exception {
    public:
        [[nodiscard]] const char* what() const noexcept override;
    };

    template<class T>
    class Ref final{
    public:
        Ref() = delete;

        explicit constexpr Ref(T* pointer):
            m_pointer(pointer)
        {
            if(m_pointer == nullptr){
                throw NullPointerException();
            }
        }

        constexpr Ref(const Ref&) = default;
        constexpr Ref(Ref&& from) noexcept :
            m_pointer(from.m_pointer)
        {
            from.m_pointer = nullptr;
        }

        ~Ref() = default;

        constexpr Ref<T>& operator=(const Ref<T>& from){
            if(this != &from){
                m_pointer = from.m_pointer;
            }
            return *this;
        }

        constexpr Ref<T>& operator=(Ref<T>&& from) noexcept{
            if(this != &from){
                m_pointer = from.m_pointer;
                from.m_pointer = nullptr;
            }
            return *this;
        }

        constexpr T& operator*(){
            return *m_pointer;
        }

        constexpr const T& operator*() const{
            return *m_pointer;
        }

    private:
        T* m_pointer;
    };

    template<class T>
    class OptionalRef final{
    public:
        constexpr OptionalRef() = default;

        constexpr OptionalRef(T* pointer): /* NOLINT(hicpp-explicit-conversions) */
            m_pointer(pointer)
        {}

        constexpr explicit OptionalRef(T& pointer):
                m_pointer(&pointer)
        {}

        constexpr OptionalRef(const OptionalRef&) = default;

        constexpr OptionalRef(OptionalRef&& from) noexcept:
            m_pointer(from.m_pointer)
        {
            from.m_pointer = nullptr;
        };

        ~OptionalRef() = default;

        constexpr OptionalRef<T>& operator=(const OptionalRef<T>&) = default;

        constexpr OptionalRef<T>& operator=(OptionalRef&& from) noexcept {
            if(this != &from){
                m_pointer = from.m_pointer;
                m_pointer = nullptr;
            }
            return *this;
        }

        constexpr bool operator==(const T* other) const{
            return m_pointer == other;
        };

    private:
        T* m_pointer = nullptr;
    };
}

#endif //CYBERCRAFT_POINTER_H
