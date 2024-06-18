#pragma once
#include "defines.h"


// - - - | Vector | - - -


// - - - 2D Vector - - -

typedef union Vector2D
{
    float elements[2];
    struct 
    {
        union
        {
            float x, r, s, u;
        };
        union
        {
            float y, g, t, v;
        };
    };
} Vector2D;


// - - - 3D Vector - - -

typedef union Vector3D
{
    float elements[3];
    struct 
    {
        union
        {
            float x, r, s, u;
        };
        union
        {
            float y, g, t, v;
        };
        union
        {
            float z, b, p, w;
        };
    };
} Vector3D;


// - - - 4D Vector - - -

typedef union Vector4D
{
    float elements[4];
    struct 
    {
        union
        {
            float x, r, s;
        };
        union
        {
            float y, g, t;
        };
        union
        {
            float z, b, p;
        };
        union
        {
            float w, a, q;
        };
    };
} Vector4D;

typedef Vector4D Quaternion;
/*
struct Vector2
{
    float x, y;

    Vector2() : x(0), y(0) {}
    Vector2(float x, float y) : x(x), y(y) {}

    Vector2 operator+(const Vector2& v) const { return Vector2(x + v.x, y + v.y); }
    Vector2 operator-(const Vector2& v) const { return Vector2(x - v.x, y - v.y); }
    Vector2 operator*(float s) const { return Vector2(x * s, y * s); }
    Vector2 operator/(float s) const { return Vector2(x / s, y / s); }

    Vector2& operator+=(const Vector2& v) { x += v.x; y += v.y; return *this; }
    Vector2& operator-=(const Vector2& v) { x -= v.x; y -= v.y; return *this; }
    Vector2& operator*=(float s) { x *= s; y *= s; return *this; }
    Vector2& operator/=(float s) { x /= s; y /= s; return *this; }

    float dot(const Vector2& v) const { return x * v.x + y * v.y; }
    float cross(const Vector2& v) const { return x * v.y - y * v.x; }
    float length() const { return sqrtf(x * x + y * y); }
    float lengthSquared() const { return x * x + y * y; }
    Vector2 normalized() const { return *this / length(); }
    Vector2& normalize() { return *this /= length(); }
};
*/
