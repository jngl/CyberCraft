//
// Created by jngl on 21/05/2020.
//

#include "Camera.h"

#include "Math.h"

sf::View createDefaultView(){
	return sf::View(sf::Vector2f(0, 0), sf::Vector2f (400, 300));
}

void moveViewTo(sf::View& view, sf::Vector2f target, float minSpeed, float lengthSpeedFactor){
	const sf::Vector2f& center = view.getCenter();

	sf::Vector2f diff = target - center;
	float length = math::length(diff);

	sf::Vector2f move;

	float speed2 = length / lengthSpeedFactor + minSpeed;

	if(length > speed2){
		move = diff / length * speed2;
        view.setCenter(center + move);
	}else{
        view.setCenter(target);
	}
}