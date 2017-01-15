#ifndef __SGE_COLLISION_SHAPE_NODE_HPP
#define __SGE_COLLISION_SHAPE_NODE_HPP

#include <sge/nodes/position.hpp>
#include <sge/physics/shape.hpp>

namespace sge
{
    class CollisionShapeNode : public PositionNode
    {
        using PositionNode::PositionNode;

        public:
            virtual std::vector<std::string> mro() const;

            void set_shape(const Shape &shape);
            Shape get_shape() const;

        private:
            Shape _shape;
    };
}

#endif /* __SGE_COLLISION_SHAPE_NODE_HPP */
