//
// Created by jngl on 28/04/2020.
//

#ifndef CYBERCRAFT_MATH_H
#define CYBERCRAFT_MATH_H

#include <cmath>

namespace math{
    template<class T>
    struct Vector2
    {
        T x = 0;
        T y = 0;

        Vector2<T> operator*(T value) const {
            return {x*value, y*value};
        }

        Vector2<T> operator+(const Vector2<T>& right) const {
            return {x+right.x, y+right.y};
        }
    };

    using Vector2i = Vector2<int>;
    using Vector2f = Vector2<float>;

	template<class T>
	T length(const math::Vector2<T>& vec){
		return sqrt(vec.x*vec.x+vec.y*vec.y);
	}
}

#endif //CYBERCRAFT_CONVERSION_H
