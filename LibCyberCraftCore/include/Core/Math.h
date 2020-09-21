//
// Created by jngl on 28/04/2020.
//

#ifndef CYBERCRAFT_MATH_H
#define CYBERCRAFT_MATH_H

#include <cmath>
#include <array>

namespace ccCore{
    template<class T>
    struct Vector2
    {
        T x = 0;
        T y = 0;

        constexpr Vector2() = default;
        constexpr Vector2(const Vector2<T>&) = default;
        constexpr explicit Vector2(T value):
            x(value),
            y(value)
        {}
        constexpr Vector2(T p_x, T p_y):
            x(p_x),
            y(p_y)
        {}

        Vector2<T> operator*(T value) const {
            return {x*value, y*value};
        }

        Vector2<T> operator+(const Vector2<T>& right) const {
            return {x+right.x, y+right.y};
        }

        bool isInRect(T minX, T maxX, T minY, T maxY){
            return x>=minX || x<=maxX ||
                   y>=minY || y<=maxY;
        }

        template<class T2>
        Vector2<T2> toVector() {
            return Vector2<T2>{static_cast<T2>(x), static_cast<T2>(y)};
        }
    };

    using Vector2i = Vector2<int>;
    using Vector2f = Vector2<float>;

	template<class T>
	T length(const Vector2<T>& vec){
		return sqrt(vec.x*vec.x+vec.y*vec.y);
	}

    template<class T>
    struct Matrix4{
		    std::array<T, 16> data;
	};

	using Matrix4f = Matrix4<float>;
}

#endif //CYBERCRAFT_CONVERSION_H
