#include <sge/physics/shape.hpp>
#include <algorithm>

using namespace std;

namespace sge
{
    Shape::Shape() {}

    Shape::Shape(const vector<Vector> &vertices) : vertices(vertices)
    {
        Vector barycenter(0, 0);

        for (auto it = vertices.begin(); it != vertices.end(); it++)
        {
            barycenter = barycenter + *it;
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

        barycenter = barycenter / (float) vertices.size();

        for (auto &vertex : vertices)
        {
            vertex = vertex - barycenter;
        }

        for (auto &edge : edges)
        {
            edge.start = edge.start - barycenter;
            edge.end = edge.end - barycenter;
        }
    }

    Shape Shape::translate(const Vector &v) const
    {
        vector<Vector> t_vertices;

        for (auto vertex : vertices)
        {
            t_vertices.push_back(vertex + v);
        }

        return Shape(t_vertices);
    }

    Shape Shape::rotate(float angle) const
    {
        vector<Vector> r_vertices;

        for (auto vertex : vertices)
        {
            r_vertices.push_back(vertex.rotate(angle));
        }

        return Shape(r_vertices);
    }

    vector<float> Shape::projection(const Vector &v) const
    {
        vector<Vector> projected;

        for (auto vertex : vertices)
        {
            projected.push_back(vertex.projection(v));
        }

        vector<float> result;
        Vector axis(1.0, 0.0);

        for (auto p : projected)
        {
            result.push_back(p.projection(axis).x);
        }

        sort(result.begin(), result.end());

        return result;
    }

    bool Shape::overlap(const Shape &other, Vector &mtv) const
    {
        float penetration = 0.0;

        for (auto edge : edges)
        {
            Vector n = edge.as_vector().normal();
            vector<float> a_proj = projection(n);
            vector<float> b_proj = other.projection(n);

            float ax1 = a_proj.front();
            float ax2 = a_proj.back();
            float bx1 = b_proj.front();
            float bx2 = b_proj.back();

            float i1 = max(ax1, bx1);
            float i2 = min(ax2, bx2);

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
}
