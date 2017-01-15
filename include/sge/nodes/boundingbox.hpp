#ifndef __SGE_BOUDING_BOX_NODE_HPP
#define __SGE_BOUDING_BOX_NODE_HPP

#include <sge/nodes/position.hpp>

namespace sge
{
    class BoundingBoxNode : public PositionNode
    {
        using PositionNode::PositionNode;

        public:
            virtual std::vector<std::string> mro() const;

            void set_box(int w, int h);
            void set_box(SDL_Point box);
            SDL_Point get_box() const;

        private:
            SDL_Point size;
    };
}

#endif /* __SGE_BOUDING_BOX_NODE_HPP */
