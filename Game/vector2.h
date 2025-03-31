#ifndef VECTOR2_H
#define VECTOR2_H

struct Vector2 {
    float x, y;
    Vector2() : x(0), y(0) {}
    Vector2(float x, float y) : x(x), y(y) {}
    // Addition
    Vector2 operator+(const Vector2& v) const { return Vector2(x + v.x, y + v.y); }
    Vector2& operator+=(const Vector2& v) { x += v.x; y += v.y; return *this; }
    // Subtraction
    Vector2 operator-(const Vector2& v) const { return Vector2(x - v.x, y - v.y); }
    Vector2& operator-=(const Vector2& v) { x -= v.x; y -= v.y; return *this; }
    // Multiplication
    Vector2 operator*(float scalar) const { return Vector2(x * scalar, y * scalar); }
    Vector2& operator*=(float scalar) { x *= scalar; y *= scalar; return *this; }
    // Division
    Vector2 operator/(float scalar) const { return Vector2(x / scalar, y / scalar); }
    Vector2& operator/=(float scalar) { x /= scalar; y /= scalar; return *this; }
};

#endif
