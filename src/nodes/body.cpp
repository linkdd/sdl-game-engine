#include <sge/nodes/body.hpp>
#include <sge/engine.hpp>

using namespace std;

namespace sge
{
    vector<string> BodyNode::mro() const
    {
        auto _mro = PositionNode::mro();
        _mro.push_back("BodyNode");
        return _mro;
    }

    bool BodyNode::is_colliding() const
    {
        return colliding;
    }
}
