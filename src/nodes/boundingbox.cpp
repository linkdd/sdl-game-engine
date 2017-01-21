#include <sge/nodes/boundingbox.hpp>
#include <sge/engine.hpp>

using namespace std;

namespace sge
{
    vector<string> BoundingBoxNode::mro() const
    {
        auto _mro = PositionNode::mro();
        _mro.push_back("BoundingBoxNode");
        return _mro;
    }

    void BoundingBoxNode::set_box(int w, int h)
    {
        size.x = w;
        size.y = h;
    }

    void BoundingBoxNode::set_box(SDL_Point box)
    {
        set_box(box.x, box.y);
    }

    SDL_Point BoundingBoxNode::get_box() const
    {
        return size;
    }
}
