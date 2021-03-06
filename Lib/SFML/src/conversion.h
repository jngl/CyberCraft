//
// Created by jngl on 29/08/2020.
//

#ifndef CYBERCRAFT_CONVERSION_H
#define CYBERCRAFT_CONVERSION_H

#include <Core/Math.h>
#include <Core/Color.h>

#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics/Color.hpp>

namespace ccSf {
    template<class T>
    sf::Vector2<T> toSfVector2(const cc::Vector2 <T> &v) {
        return sf::Vector2<T>(v.x, v.y);
    }

    sf::Color toSfColor(const cc::Color &c);
}

#endif //CYBERCRAFT_CONVERSION_H
