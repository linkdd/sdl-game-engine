#ifndef __SGE_NODE_MANAGER_HPP
#define __SGE_NODE_MANAGER_HPP

#include <sge/node.hpp>
#include <map>

namespace sge
{
    class NodeManager
    {
        public:
            NodeManager(Engine &engine);

            template <class NodeType>
            std::shared_ptr<NodeType> create(const std::string &nodename)
            {
                std::shared_ptr<NodeType> node = std::make_shared<NodeType>(nodename, engine);
                node->init();
                nodes[node] = false;
                return node;
            }

            void garbage_collect();

        private:
            void mark(std::shared_ptr<Node> root);

        private:
            Engine &engine;
            std::map<std::shared_ptr<Node>, bool> nodes;

    };
}

#endif /* __SGE_NODE_MANAGER_HPP */
