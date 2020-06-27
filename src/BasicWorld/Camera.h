//
// Created by jngl on 21/05/2020.
//

#ifndef CYBERCRAFT_CAMERA_H
#define CYBERCRAFT_CAMERA_H

#include "../Core/Common.h"

sf::View createDefaultView();

void moveViewTo(sf::View& view, sf::Vector2f target, float minSpeed, float lengthSpeedFactor);

#endif //CYBERCRAFT_CAMERA_H
