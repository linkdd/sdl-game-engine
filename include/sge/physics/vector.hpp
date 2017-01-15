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
        Vector(int x, int y) : x(x), y(y) {}
        Vector(SDL_Point p) : x(p.x), y(p.y) {}

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

        Vector normal() const
        {
            Vector result;
            result.x = -y;
            result.y = x;
            return result;
        }

        Vector projection(const Vector &v) const
        {
            return v * (dot(v) / v.magnitude_squared());
        }

        Vector operator+(const Vector &other) const
        {
            Vector result;
            result.x = x + other.x;
            result.y = y + other.y;
            return result;
        }

        Vector operator-(const Vector &other) const
        {
            Vector result;
            result.x = x - other.x;
            result.y = y - other.y;
            return result;
        }

        Vector operator*(float n) const
        {
            Vector result;
            result.x = x * n;
            result.y = y * n;
            return result;
        }

        Vector operator/(float n) const
        {
            Vector result;
            result.x = x / n;
            result.y = y / n;
            return result;
        }
    };
}

#endif /* __SGE_VECTOR_HPP */