#include <sge/nodes/position.hpp>

namespace sge
{
    std::vector<std::string> PositionNode::mro() const
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

    SDL_Point PositionNode::get_absolute_pos()
    {
        SDL_Point abs_pos = {0, 0};

        std::shared_ptr<Node> node = shared_from_this();

        while (node != nullptr)
        {
            if (node->is_of("PositionNode"))
            {
                auto pnode = std::static_pointer_cast<PositionNode>(node);
                SDL_Point pos = pnode->get_pos();
                abs_pos.x += pos.x;
                abs_pos.y += pos.y;
            }

            node = node->get_parent();
        }

        return abs_pos;
    }
}
