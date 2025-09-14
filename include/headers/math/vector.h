#pragma once

struct Vector
{

    float x, y;

    void set(float x, float y);

    float length();
    Vector normal();
    void normalize();

    float distance(const Vector &v);
    float distanceSquared(const Vector &v);
    float dot(const Vector &v);
    float cross(const Vector &v);

    inline Vector operator+(const Vector &v)
    {
        return Vector{x + v.x, y + v.y};
    }
    inline Vector operator-(const Vector &v)
    {
        return Vector{x - v.x, y - v.y};
    }
    inline Vector operator*(const float scalar)
    {
        return Vector{x * scalar, y * scalar};
    }
    inline Vector operator/(const float scalar)
    {
        return Vector{x / scalar, y / scalar};
    }

    inline Vector &operator+=(const Vector &v)
    {
        x += v.x;
        y += v.y;
        return *this;
    }
    inline Vector &operator-=(const Vector &v)
    {
        x -= v.x;
        y -= v.y;
        return *this;
    }
    inline Vector &operator*=(const float scalar)
    {
        x *= scalar;
        y *= scalar;
        return *this;
    }
    inline Vector &operator/=(const float scalar)
    {
        x /= scalar;
        y /= scalar;
        return *this;
    }
};