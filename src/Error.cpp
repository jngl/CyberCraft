//
// Created by jngl on 27/04/2020.
//

#include "Error.h"

Error::Error(std::string_view msg) :
		m_message(msg) {}

const char *Error::what() const noexcept {
	return m_message.c_str();
}
