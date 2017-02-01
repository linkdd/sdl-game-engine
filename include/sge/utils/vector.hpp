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

        SDL_Point as_point() const
        {
            SDL_Point result;
            result.x = x;
            result.y = y;
            return result;
        }

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

        Vector rotate(float angle) const
        {
            return Vector(
                x * cos(angle) + y * sin(angle),
                - x * sin(angle) + y * cos(angle)
            );
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

    Vector VectorPolar(float angle, float r);

    Vector operator*(int i, const Vector &v);
    Vector operator*(float f, const Vector &v);
    Vector operator-(const Vector &v);
}

#endif /* __SGE_VECTOR_HPP */