#ifndef __SGE_POSITION_NODE_HPP
#define __SGE_POSITION_NODE_HPP

#include <sge/node.hpp>

namespace sge
{
    class PositionNode : public Node
    {
        using Node::Node;

        public:
            virtual std::vector<std::string> mro() const;

            SDL_Point get_pos() const;
            void set_pos(const SDL_Point &pos);
            void set_pos(int x, int y);

            SDL_Point get_absolute_pos();

        private:
            SDL_Point _pos;
    };
}

#endif /* __SGE_POSITION_NODE_HPP */
