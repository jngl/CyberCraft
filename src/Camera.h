//
// Created by jngl on 21/05/2020.
//

#ifndef CYBERCRAFT_CAMERA_H
#define CYBERCRAFT_CAMERA_H

#include <SFML/Graphics.hpp>

class Camera{
public:
	Camera();

	void set(sf::RenderTarget& renderTarget);

	void moveTo(sf::Vector2f target, float speed);

private:
	sf::View m_view;
};

#endif //CYBERCRAFT_CAMERA_H
