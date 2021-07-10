//
// Created by jngl on 05/12/2020.
//

#ifndef CYBERCRAFT_TYPENAME_H
#define CYBERCRAFT_TYPENAME_H

#include <string_view>

// https://stackoverflow.com/questions/81870/is-it-possible-to-print-a-variables-type-in-standard-c/56766138#56766138

namespace cc {

    namespace impl {
        template<class T>
        constexpr std::string_view rawTypeName() {
            #if defined(__clang__)
            return __PRETTY_FUNCTION__;
            #elif defined(__GNUC__)
            return __PRETTY_FUNCTION__;
            #elif defined(_MSC_VER)
            return __PRETTY_FUNCTION__;
            #else
            # error "compileur not supported"
            #endif
        }

        constexpr std::string_view doubleRawTypeName = rawTypeName<double>();
        constexpr size_t doubleTypeNameLength = std::string_view("double").size();

        constexpr size_t prefixLength = doubleRawTypeName.find("double");
        static_assert(prefixLength != std::string_view::npos,
                      "cannot extract typename from function signature");

        constexpr size_t suffixLength = doubleRawTypeName.size() - prefixLength - doubleTypeNameLength;
    }

    template <class T>
    constexpr std::string_view typeName() noexcept {
        std::string_view name = impl::rawTypeName<T>();
        return std::string_view(name.data() + impl::prefixLength,
                                name.size() - impl::prefixLength - impl::suffixLength);
    }
}

#endif //CYBERCRAFT_TYPENAME_H
