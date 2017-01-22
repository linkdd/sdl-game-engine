#ifndef __SGE_SHAPE_HPP
#define __SGE_SHAPE_HPP

#include <sge/physics/vector.hpp>
#include <vector>

namespace sge
{
    struct Edge
    {
        Vector start;
        Vector end;

        Edge(Vector s, Vector e) : start(s), end(e) {}

        Vector as_vector() const
        {
            return end - start;
        }
    };

    class Shape
    {
        public:
            Shape();
            Shape(const std::vector<Vector> &vertices);

            Shape translate(const Vector &v) const;
            Vector barycenter() const;
            Shape rotate(float angle) const;
            std::vector<float> projection(const Vector &v) const;
            bool overlap(const Shape &other, Vector &mtv) const;

        private:
            std::vector<Vector> vertices;
            std::vector<Edge> edges;
    };
}

#endif /* __SGE_SHAPE_HPP */
