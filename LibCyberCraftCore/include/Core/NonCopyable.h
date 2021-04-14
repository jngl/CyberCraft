//
// Created by jngl on 28/03/2021.
//

#ifndef CYBERCRAFT_NONCOPYABLE_H
#define CYBERCRAFT_NONCOPYABLE_H

namespace cc
{
    class NonCopyable{
    public:
        NonCopyable() = default;
        NonCopyable(const NonCopyable&) = delete;
        NonCopyable(NonCopyable&&) = delete;

        NonCopyable& operator=(const NonCopyable&) = delete;
        NonCopyable& operator=(NonCopyable&&) = delete;

        virtual ~NonCopyable() = default;
    };
}

#endif //CYBERCRAFT_NONCOPYABLE_H
