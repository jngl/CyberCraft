//
// Created by jngl on 21/05/2020.
//

#ifndef CYBERCRAFT_CAMERA_H
#define CYBERCRAFT_CAMERA_H

#include <SFML/Graphics.hpp>

sf::View createDefaultView();

void moveViewTo(sf::View& view, sf::Vector2f target, float minSpeed, float lengthSpeedFactor);

#endif //CYBERCRAFT_CAMERA_H
