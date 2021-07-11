//
// Created by jngl on 11/07/2021.
//

#include "Kernel/Graphics.h"

namespace ck{
    GraphicsError::GraphicsError(std::string_view msg)
    {
        m_message = std::string("System Error : ") + std::string(msg);
    }

    [[nodiscard]] const char* GraphicsError::what() const noexcept{
        return m_message.c_str();
    }
}
