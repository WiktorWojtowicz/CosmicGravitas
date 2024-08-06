#ifndef VECTOR2_HPP
#define VECTOR2_HPP

#include <iostream>
#include <cmath>
#include "const.hpp"

class Vector2 {
public:
    large_float x, y;

    Vector2(large_float x = 0, large_float y = 0);

    void normalize();
    large_float dot(const Vector2& other) const;
    large_float cross(const Vector2& other) const;
    large_float magnitude() const;
    large_float squaredMagnitude() const;

    Vector2& operator+=(const Vector2& other);
    Vector2& operator-=(const Vector2& other);
    Vector2& operator*=(const Vector2& other);
    Vector2& operator/=(const Vector2& other);

    Vector2& operator+=(const large_float& scalar);
    Vector2& operator-=(const large_float& scalar);
    Vector2& operator*=(const large_float& scalar);
    Vector2& operator/=(const large_float& scalar);

    Vector2 operator+(const Vector2& other) const;
    Vector2 operator-(const Vector2& other) const;
    Vector2 operator*(const Vector2& other) const;
    Vector2 operator/(const Vector2& other) const;

    Vector2 operator+(const large_float& scalar) const;
    Vector2 operator-(const large_float& scalar) const;
    Vector2 operator*(const large_float& scalar) const;
    Vector2 operator/(const large_float& scalar) const;

    bool operator==(const Vector2& other) const;
    bool operator!=(const Vector2& other) const;

    Vector2 abs();

    static Vector2 zero();
    static Vector2 unitX();
    static Vector2 unitY();

    friend std::ostream& operator<<(std::ostream& os, const Vector2& v);
};

#endif // VECTOR2_HPP
