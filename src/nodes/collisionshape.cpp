#include <sge/nodes/collisionshape.hpp>
#include <sge/engine.hpp>

using namespace std;

namespace sge
{
    vector<string> CollisionShapeNode::mro() const
    {
        auto _mro = PositionNode::mro();
        _mro.push_back("CollisionShapeNode");
        return _mro;
    }

    void CollisionShapeNode::set_shape(const Shape &shape)
    {
        _shape = shape;
    }

    Shape CollisionShapeNode::get_shape()
    {
        Vector pos(get_pos());
        Vector abspos(get_absolute_pos());

        return _shape.translate(abspos - pos).rotate(get_absolute_rotation());
    }
}
