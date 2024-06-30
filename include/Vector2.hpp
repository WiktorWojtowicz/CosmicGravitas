#ifndef VECTOR2_HPP
#define VECTOR2_HPP

#include <iostream>
#include <cmath>

class Vector2 {
public:
    double x, y;

    Vector2(double x = 0, double y = 0) : x(x), y(y) { }

    void normalize() {
        double l = sqrt(x * x + y * y);
        if (l > 0) {
            x /= l;
            y /= l;
        }
    }

    double dot(const Vector2& other) const {
        return x * other.x + y * other.y;
    }

    double cross(const Vector2& other) const {
        return x * other.y - y * other.x;
    }

    double magnitude() const {
        return sqrt(x * x + y * y);
    }

    double squaredMagnitude() const {
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

    Vector2& operator+=(const double& scalar) {
        x += scalar;
        y += scalar;
        return *this;
    }

    Vector2& operator-=(const double& scalar) {
        x -= scalar;
        y -= scalar;
        return *this;
    }

    Vector2& operator*=(const double& scalar) {
        x *= scalar;
        y *= scalar;
        return *this;
    }

    Vector2& operator/=(const double& scalar) {
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

    Vector2 operator+(const double& scalar) const {
        Vector2 result = *this;
        result += scalar;
        return result;
    }

    Vector2 operator-(const double& scalar) const {
        Vector2 result = *this;
        result -= scalar;
        return result;
    }

    Vector2 operator*(const double& scalar) const {
        Vector2 result = *this;
        result *= scalar;
        return result;
    }

    Vector2 operator/(const double& scalar) const {
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