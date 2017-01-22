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

            int get_rotation() const;
            void set_rotation(int angle);

            SDL_Point get_absolute_pos() const;
            int get_absolute_rotation() const;

        private:
            SDL_Point _pos;
            int _angle = 0;
    };
}

#endif /* __SGE_POSITION_NODE_HPP */
