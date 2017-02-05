#ifndef __SGE_NODE_MANAGER_HPP
#define __SGE_NODE_MANAGER_HPP

#include <sge/node.hpp>

namespace sge
{
    class NodeManager
    {
        public:
            NodeManager(Engine &engine) : engine(engine) {}

            template <class NodeType>
            std::shared_ptr<NodeType> create(const std::string &nodename)
            {
                std::shared_ptr<NodeType> node = std::make_shared<NodeType>(nodename, engine);
                node->init();
                return node;
            }

        private:
            Engine &engine;

    };
}

#endif /* __SGE_NODE_MANAGER_HPP */
