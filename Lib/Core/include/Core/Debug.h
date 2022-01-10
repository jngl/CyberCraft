//
// Created by jngl on 27/04/2020.
//

#ifndef CYBERCRAFT_DEBUG_H
#define CYBERCRAFT_DEBUG_H
//
//#include <string>
//#include <exception>
//#include <iostream>
//
//#include <CyberBase/Error.hpp>
//
//namespace cc {
//    namespace impl
//    {
//        template <typename T>
//        void log2(T t)
//        {
//            std::cout << t;
//        }
//
//        template<typename T, typename... Args>
//        void log2(T t, Args... args) // recursive variadic function
//        {
//            std::cout << t;
//
//            log2(args...) ;
//        }
//    }
//
//    template<typename... Args>
//    void log(std::string_view module, Args... args) // recursive variadic function
//    {
//        std::cout << module << " : " ;
//
//        impl::log2(args...) ;
//
//        std::cout  <<std::endl ;
//    }
//
//    template<typename... Args>
//    void check(std::string_view module, bool cond, Args... args) // recursive variadic function
//    {
//        if(cond) {
//            return;
//        }
//
//        std::cout<< "[" << module << "] assert error in "<< module << " : " ;
//
//        impl::log2(args...) ;
//
//        std::cout  <<std::endl ;
//
//        exit(1);
//    }
//}

#endif //CYBERCRAFT_DEBUG_H
