//
// Created by jngl on 27/04/2020.
//

#ifndef CYBERCRAFT_ERROR_H
#define CYBERCRAFT_ERROR_H

#include <string>
#include <exception>

namespace ccCore {
    class Error : public std::exception {
    public:
        explicit Error(std::string_view msg);

        [[nodiscard]] const char *what() const noexcept override;

    private:
        std::string m_message;
    };
}
#endif //CYBERCRAFT_ERROR_H
