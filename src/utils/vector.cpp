#include <sge/utils/vector.hpp>

namespace sge
{
    Vector VectorPolar(float angle, float r)
    {
        return Vector(
            r * cos(angle),
            r * sin(angle)
        );
    }

    Vector operator*(int i, const Vector &v)
    {
        return v * i;
    }

    Vector operator*(float f, const Vector &v)
    {
        return v * f;
    }

    Vector operator-(const Vector &v)
    {
        return -1 * v;
    }
}
