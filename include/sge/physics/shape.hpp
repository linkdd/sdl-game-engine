#ifndef __SGE_SHAPE_HPP
#define __SGE_SHAPE_HPP

#include <sge/physics/vector.hpp>

#include <algorithm>
#include <vector>

namespace sge
{
    struct Edge
    {
        Vector start;
        Vector end;

        Vector as_vector() const
        {
            return end - start;
        }
    };

    struct Shape
    {
        std::vector<Vector> vertices;
        std::vector<Edge> edges;

        Shape translate(const Vector &v) const
        {
            Shape result;

            for (auto vertex : vertices)
            {
                result.vertices.push_back(vertex + v);
            }

            for (auto edge : edges)
            {
                Edge new_edge;
                new_edge.start = edge.start + v;
                new_edge.end = edge.end + v;
                result.edges.push_back(new_edge);
            }

            return result;
        }

        std::vector<int> projection(const Vector &v) const
        {
            std::vector<Vector> projected;

            for (auto vertex : vertices)
            {
                projected.push_back(vertex.projection(v));
            }

            std::vector<int> result;
            Vector axis(1, 0);

            for (auto p : projected)
            {
                result.push_back(p.projection(axis).x);
            }

            std::sort(result.begin(), result.end());

            return result;
        }

        bool overlap(const Shape &other) const
        {
            for (auto edge : edges)
            {
                Vector n = edge.as_vector().normal();
                std::vector<int> a_proj = projection(n);
                std::vector<int> b_proj = other.projection(n);

                int ax1 = a_proj.front();
                int ax2 = a_proj.back();
                int bx1 = b_proj.front();
                int bx2 = b_proj.back();

                if (!((ax1 <= bx1 <= ax2) || (ax1 <= bx2 <= ax2)))
                {
                    return false;
                }
            }

            return true;
        }
    };
}

#endif /* __SGE_SHAPE_HPP */
