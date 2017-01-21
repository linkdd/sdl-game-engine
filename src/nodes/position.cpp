#include <sge/nodes/position.hpp>

using namespace std;

namespace sge
{
    vector<string> PositionNode::mro() const
    {
        auto _mro = Node::mro();
        _mro.push_back("PositionNode");
        return _mro;
    }

    SDL_Point PositionNode::get_pos() const
    {
        return _pos;
    }

    void PositionNode::set_pos(const SDL_Point &pos)
    {
        _pos.x = pos.x;
        _pos.y = pos.y;
    }

    void PositionNode::set_pos(int x, int y)
    {
        _pos.x = x;
        _pos.y = y;
    }

    int PositionNode::get_rotation() const
    {
        return _angle;
    }

    void PositionNode::set_rotation(int angle)
    {
        _angle = (_angle + angle) % 360;
    }

    SDL_Point PositionNode::get_absolute_pos()
    {
        SDL_Point abs_pos = {0, 0};

        shared_ptr<Node> node = shared_from_this();

        while (node != nullptr)
        {
            if (node->is_of("PositionNode"))
            {
                auto pnode = static_pointer_cast<PositionNode>(node);
                SDL_Point pos = pnode->get_pos();
                abs_pos.x += pos.x;
                abs_pos.y += pos.y;
            }

            node = node->get_parent();
        }

        return abs_pos;
    }

    int PositionNode::get_absolute_rotation()
    {
        int abs_angle = 0;

        shared_ptr<Node> node = shared_from_this();

        while (node != nullptr)
        {
            if (node->is_of("PositionNode"))
            {
                auto pnode = static_pointer_cast<PositionNode>(node);
                abs_angle += pnode->get_rotation();
            }

            node = node->get_parent();
        }

        return abs_angle % 360;
    }
}
