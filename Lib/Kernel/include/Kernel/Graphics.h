//
// Created by jngl on 11/07/2021.
//

#ifndef CYBERCRAFTKERNEL_GRAPHICS_H
#define CYBERCRAFTKERNEL_GRAPHICS_H

#include <Core/Bases.h>

#include <Kernel/Engine2D.h>
#include <Kernel/Key.h>

#include <memory>

namespace ck {
    class GraphicsError : public std::exception
    {
    public:
        explicit GraphicsError(std::string_view msg);
        [[nodiscard]] const char* what() const noexcept override;
    private:
        std::string m_message;
    };

    class KeyListener
    {
    public:
        virtual ~KeyListener() = default;

        virtual void onKeyUp(ck::Key key) = 0;
        virtual void onKeyDown(ck::Key key) = 0;
    };

    class ExitListener
    {
    public:
        virtual ~ExitListener() = default;

        virtual void onExit() = 0;
    };

    class Frame : public cc::NonCopyable
    {
    public:
        virtual ck::ColoredRectangleDrawer& getColoredRectangleDrawer() = 0;
    };
}

#endif //CYBERCRAFT_GRAPHICS_H
