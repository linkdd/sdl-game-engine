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
        SDL_Point pos = get_pos();

        size.x = w;
        size.y = h;

        pos.x = -(w / 2);
        pos.y = -(h / 2);

        set_pos(pos);
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
