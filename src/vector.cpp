#include "utils/vector.h"
#include <cmath>

float Vector::length()
{
    return sqrt(x * x + y * y);
}

Vector Vector::normal()
{
    return *this / length();
}

void Vector::normalize()
{
    x /= length();
    y /= length();
}

float Vector::distance(const Vector &v)
{
    return (*this - v).length();
}

float Vector::dot(const Vector &v)
{
    return x * v.x + y * v.y;
}