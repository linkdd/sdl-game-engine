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

        pre_multiply_transform();
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

        pre_multiply_transform();
    }

    Matrix<3,3> PositionNode::get_pm_transform() const
    {
        return pm_transform;
    }

    void PositionNode::pre_multiply_transform()
    {
        pm_transform = rotation * translation;
        auto parent = find_first_ancestor_by_type("PositionNode");

        if (parent != nullptr)
        {
            auto pnode = static_pointer_cast<PositionNode>(parent);
            pm_transform = pnode->get_pm_transform() * pm_transform;
        }
    }

    Vector PositionNode::get_absolute_pos() const
    {
        Matrix<3,1> origin = {
            {0.0},
            {0.0},
            {1.0}
        };
        Matrix<3,1> transformed = pm_transform * origin;

        return Vector(transformed(0, 0), transformed(1, 0));
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
}
