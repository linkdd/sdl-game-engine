#ifndef __SGE_BODY_NODE_HPP
#define __SGE_BODY_NODE_HPP

#include <sge/nodes/position.hpp>
#include <sge/physics/manager.hpp>

namespace sge
{
    class BodyNode : public PositionNode
    {
        friend class PhysicManager;
        using PositionNode::PositionNode;

        public:
            virtual std::vector<std::string> mro() const;

            bool is_colliding() const;

        private:
            bool colliding;
    };
}

#endif /* __SGE_BODY_NODE_HPP */
