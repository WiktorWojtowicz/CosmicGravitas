#include "Vector2.hpp"

Vector2::Vector2(large_float x, large_float y) : x(x), y(y) { }

void Vector2::normalize() {
    large_float l = sqrt(x * x + y * y);
    if (l > 0) {
        x /= l;
        y /= l;
    }
}

large_float Vector2::dot(const Vector2& other) const {
    return x * other.x + y * other.y;
}

large_float Vector2::cross(const Vector2& other) const {
    return x * other.y - y * other.x;
}

large_float Vector2::magnitude() const {
    return sqrt(squaredMagnitude());
}

large_float Vector2::squaredMagnitude() const {
    return x * x + y * y;
}

Vector2& Vector2::operator+=(const Vector2& other) {
    x += other.x;
    y += other.y;
    return *this;
}

Vector2& Vector2::operator-=(const Vector2& other) {
    x -= other.x;
    y -= other.y;
    return *this;
}

Vector2& Vector2::operator*=(const Vector2& other) {
    x *= other.x;
    y *= other.y;
    return *this;
}

Vector2& Vector2::operator/=(const Vector2& other) {
    x /= other.x;
    y /= other.y;
    return *this;
}

Vector2& Vector2::operator+=(const large_float& scalar) {
    x += scalar;
    y += scalar;
    return *this;
}

Vector2& Vector2::operator-=(const large_float& scalar) {
    x -= scalar;
    y -= scalar;
    return *this;
}

Vector2& Vector2::operator*=(const large_float& scalar) {
    x *= scalar;
    y *= scalar;
    return *this;
}

Vector2& Vector2::operator/=(const large_float& scalar) {
    x /= scalar;
    y /= scalar;
    return *this;
}

Vector2 Vector2::operator+(const Vector2& other) const {
    Vector2 result;
    result.x = x + other.x;
    result.y = y + other.y;
    return result;
}

Vector2 Vector2::operator-(const Vector2& other) const {
    Vector2 result;
    result.x = x - other.x;
    result.y = y - other.y;
    return result;
}

Vector2 Vector2::operator*(const Vector2& other) const {
    Vector2 result;
    result.x = x * other.x;
    result.y = y * other.y;
    return result;
}

Vector2 Vector2::operator/(const Vector2& other) const {
    Vector2 result;
    result.x = x / other.x;
    result.y = y / other.y;
    return result;
}

Vector2 Vector2::operator+(const large_float& scalar) const {
    Vector2 result = *this;
    result += scalar;
    return result;
}

Vector2 Vector2::operator-(const large_float& scalar) const {
    Vector2 result = *this;
    result -= scalar;
    return result;
}

Vector2 Vector2::operator*(const large_float& scalar) const {
    Vector2 result = *this;
    result *= scalar;
    return result;
}

Vector2 Vector2::operator/(const large_float& scalar) const {
    Vector2 result = *this;
    result /= scalar;
    return result;
}

bool Vector2::operator==(const Vector2& other) const {
    return x == other.x && y == other.y;
}

bool Vector2::operator!=(const Vector2& other) const {
    return !(*this == other);
}

Vector2 Vector2::abs() {
    Vector2 result = *this;
    if (result.x < 0) {
        result.x *= -1;
    }
    if (result.y < 0) {
        result.y *= -1;
    }
    return result;
}

Vector2 Vector2::zero() {
    return Vector2(0.0f, 0.0f);
}

Vector2 Vector2::unitX() {
    return Vector2(1.0f, 0.0f);
}

Vector2 Vector2::unitY() {
    return Vector2(0.0f, 1.0f);
}

std::ostream& operator<<(std::ostream& os, const Vector2& v) {
    os << "(" << v.x << ", " << v.y << ")";
    return os;
}
