//
// Created by jngl on 27/04/2020.
//

#ifndef CYBERCRAFT_DEBUG_H
#define CYBERCRAFT_DEBUG_H

#include <string>
#include <exception>
#include <iostream>

namespace ccCore {
    class Error : public std::exception {
    public:
        explicit Error(std::string_view msg);

        [[nodiscard]] const char *what() const noexcept override;

    private:
        std::string m_message;
    };

    namespace
    {
        template <typename T>
        void log2(T t)
        {
            std::cout << t;
        }

        template<typename T, typename... Args>
        void log2(T t, Args... args) // recursive variadic function
        {
            std::cout << t;

            log2(args...) ;
        }
    }

    template<typename... Args>
    void log(std::string module, Args... args) // recursive variadic function
    {
        std::cout << module << " : " ;

        log2(args...) ;

        std::cout  <<std::endl ;
    }

    template<typename... Args>
    void check(std::string module, bool cond, Args... args) // recursive variadic function
    {
        if(cond)return;

        std::cout << module << "assert error in "<< module << " : " ;

        log2(args...) ;

        std::cout  <<std::endl ;

        exit(1);
    }
}

#define CC_CORE_ASSERT(module, cond) debug::assert(module, cond, "")

#endif //CYBERCRAFT_DEBUG_H
