//
// Created by jngl on 29/08/2020.
//

#include <SFML/Graphics.hpp>
#include <Core/Math.h>

#include "conversion.h"

namespace ccSf {
    sf::Color toSfColor(const cb::Color &c) {
        return sf::Color(c.red, c.green, c.blue, c.alpha);
    }
}