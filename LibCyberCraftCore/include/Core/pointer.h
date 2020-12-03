//
// Created by jngl on 03/12/2020.
//

#ifndef CYBERCRAFT_POINTER_H
#define CYBERCRAFT_POINTER_H

#include <exception>

namespace cc {
    class NullPointerException : std::exception {
    public:
        [[nodiscard]] const char* what() const noexcept override;
    };

    template<class T>
    class Ref{
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
    class OptionalRef{};
}

#endif //CYBERCRAFT_POINTER_H
