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

        Edge(Vector s, Vector e) : start(s), end(e) {}

        Vector as_vector() const
        {
            return end - start;
        }
    };

    struct Shape
    {
        std::vector<Vector> vertices;
        std::vector<Edge> edges;

        Shape() {}
        Shape(const std::vector<Vector> &vertices) : vertices(vertices)
        {
            for (auto it = vertices.begin(); it != vertices.end(); it++)
            {
                Vector start = *it;
                Vector end;

                if (next(it) == vertices.end())
                {
                    end = vertices.front();
                }
                else
                {
                    it++;
                    end = *it;
                }

                edges.push_back(Edge(start, end));
            }
        }

        Shape translate(const Vector &v) const
        {
            Shape result;

            for (auto vertex : vertices)
            {
                result.vertices.push_back(vertex + v);
            }

            for (auto edge : edges)
            {
                result.edges.push_back(Edge(edge.start + v, edge.end + v));
            }

            return result;
        }

        std::vector<float> projection(const Vector &v) const
        {
            std::vector<Vector> projected;

            for (auto vertex : vertices)
            {
                projected.push_back(vertex.projection(v));
            }

            std::vector<float> result;
            Vector axis(1.0, 0.0);

            for (auto p : projected)
            {
                result.push_back(p.projection(axis).x);
            }

            std::sort(result.begin(), result.end());

            return result;
        }

        bool overlap(const Shape &other, Vector &mtv) const
        {
            float penetration = 0.0;

            for (auto edge : edges)
            {
                Vector n = edge.as_vector().normal();
                std::vector<float> a_proj = projection(n);
                std::vector<float> b_proj = other.projection(n);

                float ax1 = a_proj.front();
                float ax2 = a_proj.back();
                float bx1 = b_proj.front();
                float bx2 = b_proj.back();

                float i1 = std::max(ax1, bx1);
                float i2 = std::min(ax2, bx2);

                if (i2 < i1)
                {
                    return false;
                }
                else
                {
                    float local_penetration = i2 - i1;

                    if (penetration == 0.0 || local_penetration < penetration)
                    {
                        penetration = local_penetration;
                        mtv = n.normalize() * penetration;
                    }
                }
            }

            return true;
        }
    };
}

#endif /* __SGE_SHAPE_HPP */
