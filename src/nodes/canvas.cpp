#include <sge/nodes/canvas.hpp>
#include <sge/engine.hpp>
#include <iostream>

using namespace std;

namespace sge
{
    vector<string> CanvasNode::mro() const
    {
        auto _mro = PositionNode::mro();
        _mro.push_back("CanvasNode");
        return _mro;
    }

    void CanvasNode::ready()
    {
        set_draw(true);
    }

    void CanvasNode::draw()
    {
        for (auto dreq : requests)
        {
            if (!dreq(engine))
            {
                cerr << "[CanvasNode][ERROR] " << engine.renderer().get_error() << endl;
            }
        }
    }
    
    void CanvasNode::clear()
    {
        requests.clear();
    }

    void CanvasNode::draw_point(Vector pos, SDL_Color color)
    {
        requests.push_back(
            [&](Engine &engine)
            {
                Vector apos = pos + get_absolute_pos();

                return engine.renderer().draw_point(apos, color);
            }
        );
    }

    void CanvasNode::draw_line(Vector start, Vector end, SDL_Color color)
    {
        requests.push_back(
            [&](Engine &engine)
            {
                Vector astart = start + get_absolute_pos();
                Vector aend = end + get_absolute_pos();

                return engine.renderer().draw_line(astart, aend, color);
            }
        );
    }

    void CanvasNode::draw_rect(SDL_Rect rect, SDL_Color color)
    {
        requests.push_back(
            [&](Engine &engine)
            {
                Vector apos = get_absolute_pos();
                SDL_Rect arect = rect;
                rect.x += apos.x;
                rect.y += apos.y;

                return engine.renderer().draw_rect(arect, color);
            }
        );
    }

    void CanvasNode::draw_filled_rect(SDL_Rect rect, SDL_Color color)
    {
        requests.push_back(
            [&](Engine &engine)
            {
                Vector apos = get_absolute_pos();
                SDL_Rect arect = rect;
                rect.x += apos.x;
                rect.y += apos.y;

                return engine.renderer().draw_filled_rect(arect, color);
            }
        );
    }

    void CanvasNode::draw_shape(const Shape &shape, SDL_Color color)
    {
        requests.push_back(
            [&](Engine &engine)
            {
                Shape ashape = shape.translate(get_absolute_pos());

                return engine.renderer().draw_shape(ashape, color);
            }
        );
    }

    void CanvasNode::draw_filled_shape(const Shape &shape, SDL_Color color)
    {
        requests.push_back(
            [&](Engine &engine)
            {
                Shape ashape = shape.translate(get_absolute_pos());

                return engine.renderer().draw_filled_shape(ashape, color);
            }
        );
    }
}
