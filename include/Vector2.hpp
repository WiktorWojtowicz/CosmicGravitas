#ifndef VECTOR2_HPP
#define VECTOR2_HPP

#include <iostream>
#include <cmath>
#include "const.hpp"

class Vector2 {
public:
    large_float x, y;

    Vector2(large_float x = 0, large_float y = 0) : x(x), y(y) { }

    void normalize() {
        large_float l = sqrt(x * x + y * y);
        if (l > 0) {
            x /= l;
            y /= l;
        }
    }

    large_float dot(const Vector2& other) const {
        return x * other.x + y * other.y;
    }

    large_float cross(const Vector2& other) const {
        return x * other.y - y * other.x;
    }

    large_float magnitude() const {
        return sqrt(x * x + y * y);
    }

    large_float squaredMagnitude() const {
        return x * x + y * y;
    }

    Vector2& operator+=(const Vector2& other) {
        x += other.x;
        y += other.y;
        return *this;
    }

    Vector2& operator-=(const Vector2& other) {
        x -= other.x;
        y -= other.y;
        return *this;
    }

    Vector2& operator*=(const Vector2& other) {
        x *= other.x;
        y *= other.y;
        return *this;
    }

    Vector2& operator/=(const Vector2& other) {
        x /= other.x;
        y /= other.y;
        return *this;
    }

    Vector2& operator+=(const large_float& scalar) {
        x += scalar;
        y += scalar;
        return *this;
    }

    Vector2& operator-=(const large_float& scalar) {
        x -= scalar;
        y -= scalar;
        return *this;
    }

    Vector2& operator*=(const large_float& scalar) {
        x *= scalar;
        y *= scalar;
        return *this;
    }

    Vector2& operator/=(const large_float& scalar) {
        x /= scalar;
        y /= scalar;
        return *this;
    }

    Vector2 operator+(const Vector2& other) const {
        Vector2 result;
        result.x = x + other.x;
        result.y = y + other.y;
        return result;
    }

    Vector2 operator-(const Vector2& other) const {
        Vector2 result;
        result.x = x - other.x;
        result.y = y - other.y;
        return result;
    }

    Vector2 operator*(const Vector2& other) const {
        Vector2 result;
        result.x = x * other.x;
        result.y = y * other.y;
        return result;
    }

    Vector2 operator/(const Vector2& other) const {
        Vector2 result;
        result.x = x / other.x;
        result.y = y / other.y;
        return result;
    }

    Vector2 operator+(const large_float& scalar) const {
        Vector2 result = *this;
        result += scalar;
        return result;
    }

    Vector2 operator-(const large_float& scalar) const {
        Vector2 result = *this;
        result -= scalar;
        return result;
    }

    Vector2 operator*(const large_float& scalar) const {
        Vector2 result = *this;
        result *= scalar;
        return result;
    }

    Vector2 operator/(const large_float& scalar) const {
        Vector2 result = *this;
        result /= scalar;
        return result;
    }

    bool operator==(const Vector2& other) const {
        return x == other.x && y == other.y;
    }

    bool operator!=(const Vector2& other) const {
        return !(*this == other);
    }

    static Vector2 zero() {
        return Vector2(0.0f, 0.0f);
    }

    static Vector2 unitX() {
        return Vector2(1.0f, 0.0f);
    }

    static Vector2 unitY() {
        return Vector2(0.0f, 1.0f);
    }

    friend std::ostream& operator<<(std::ostream& os, const Vector2& v) {
        os << "(" << v.x << ", " << v.y << ")";
        return os;
    }
};

#endif // VECTOR2_HPP