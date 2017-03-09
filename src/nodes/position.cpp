#include <sge/nodes/position.hpp>
#include <cmath>

using namespace std;

namespace sge
{
    vector<string> PositionNode::mro() const
    {
        auto _mro = Node::mro();
        _mro.push_back("PositionNode");
        return _mro;
    }

    Vector PositionNode::get_pos() const
    {
        return _pos;
    }

    void PositionNode::set_pos(const Vector &pos)
    {
        set_pos(pos.x, pos.y);
    }

    void PositionNode::set_pos(int x, int y)
    {
        _pos.x = x;
        _pos.y = y;

        translation = {
            {1.0, 0.0, (float) x},
            {0.0, 1.0, (float) y},
            {0.0, 0.0, 1.0}
        };

        local_pm_transform = translation * rotation;
        premultiply_pos();
    }

    float PositionNode::get_rotation() const
    {
        return _angle;
    }

    void PositionNode::set_rotation(float angle)
    {
        _angle = angle;

        rotation = {
            {cos(angle), sin(angle), 0.0},
            {-sin(angle), cos(angle), 0.0},
            {0.0, 0.0, 1.0}
        };

        local_pm_transform = translation * rotation;
        premultiply_pos();
    }

    float PositionNode::get_zoom() const
    {
        return _zoom;
    }

    void PositionNode::set_zoom(float zoom)
    {
        _zoom = zoom;

        translation = translation * zoom;
        local_pm_transform = translation * rotation;
        premultiply_pos();
    }

    Matrix<3,3> PositionNode::get_pm_transform() const
    {
        return local_pm_transform;
    }

    void PositionNode::premultiply_pos()
    {
        Matrix<3,1> origin = {
            {0.0},
            {0.0},
            {1.0}
        };
        Matrix<3,1> transformed = parent_pm_transform * local_pm_transform * origin;
        pm_pos = Vector(transformed(0, 0), transformed(1, 0));
    }

    Vector PositionNode::get_absolute_pos()
    {
        Matrix<3,3> current_parent_pm_transform;

        auto parent = find_first_ancestor_by_type("PositionNode");

        if (parent != nullptr)
        {
            auto pnode = static_pointer_cast<PositionNode>(parent);
            current_parent_pm_transform = pnode->get_pm_transform();
        }

        if (current_parent_pm_transform != parent_pm_transform)
        {
            parent_pm_transform = current_parent_pm_transform;
            premultiply_pos();
        }

        return pm_pos;
    }

    float PositionNode::get_absolute_rotation() const
    {
        float abs_angle = 0;

        shared_ptr<const Node> node = shared_from_this();

        while (node != nullptr)
        {
            if (node->is_of("PositionNode"))
            {
                auto pnode = static_pointer_cast<const PositionNode>(node);
                abs_angle += pnode->get_rotation();
            }

            node = node->get_parent();
        }

        return abs_angle;
    }

    float PositionNode::get_absolute_zoom() const
    {
        float abs_zoom = 1;

        shared_ptr<const Node> node = shared_from_this();

        while (node != nullptr)
        {
            if (node->is_of("PositionNode"))
            {
                auto pnode = static_pointer_cast<const PositionNode>(node);
                abs_zoom *= pnode->get_zoom();
            }

            node = node->get_parent();
        }

        return abs_zoom;
    }
}
