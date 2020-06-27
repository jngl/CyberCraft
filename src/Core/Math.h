//
// Created by jngl on 28/04/2020.
//

#ifndef CYBERCRAFT_MATH_H
#define CYBERCRAFT_MATH_H

#include <SFML/System.hpp>
#include <cmath>

namespace math{
	template<class T>
	T length(const sf::Vector2<T>& vec){
		return sqrt(vec.x*vec.x+vec.y*vec.y);
	}
}

#endif //CYBERCRAFT_MATH_H
