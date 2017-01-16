#ifndef __SGE_VECTOR_HPP
#define __SGE_VECTOR_HPP

#include <SDL.h>
#include <cmath>

namespace sge
{
    struct Vector
    {
        float x;
        float y;

        Vector() : x(0), y(0) {}
        Vector(float x, float y) : x(x), y(y) {}
        Vector(SDL_Point p) : x(p.x), y(p.y) {}

        Vector &operator=(const Vector &other)
        {
            x = other.x;
            y = other.y;
            return *this;
        }

        float dot(const Vector &other) const
        {
            return (x * other.x) + (y * other.y);
        }

        float magnitude_squared() const
        {
            return (x * x) + (y * y);
        }

        float magnitude() const
        {
            return sqrt(magnitude_squared());
        }

        Vector normalize() const
        {
            return Vector(x, y) / magnitude();
        }

        Vector normal() const
        {
            return Vector(-y, x);
        }

        Vector projection(const Vector &v) const
        {
            return v * (dot(v) / v.magnitude_squared());
        }

        Vector operator+(const Vector &other) const
        {
            return Vector(x + other.x, y + other.y);
        }

        Vector operator-(const Vector &other) const
        {
            return Vector(x - other.x, y - other.y);
        }

        Vector operator*(float n) const
        {
            return Vector(x * n, y * n);
        }

        Vector operator/(float n) const
        {
            return Vector(x / n, y / n);
        }
    };
}

#endif /* __SGE_VECTOR_HPP */