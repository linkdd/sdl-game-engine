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
        Vector pos(get_pos());
        Vector abspos(get_absolute_pos());

        _shape = shape;
        _shape.translate(abspos - pos);
    }

    Shape CollisionShapeNode::get_shape() const
    {
        return _shape;
    }
}
