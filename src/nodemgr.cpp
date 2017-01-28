#include <sge/nodemgr.hpp>
#include <sge/engine.hpp>

using namespace std;

namespace sge
{
    NodeManager::NodeManager(Engine &engine) : engine(engine) {}

    void NodeManager::garbage_collect()
    {
        for (auto it = nodes.begin(); it != nodes.end(); it++)
        {
            it->second.second = false;
        }

        mark(engine.scenes().get_scene_node());
        sweep();
    }

    void NodeManager::mark(shared_ptr<Node> root)
    {
        nodes[root].second = true;

        for (auto child : root->get_children())
        {
            mark(child);
        }
    }

    void NodeManager::sweep()
    {
        vector<NodeMap::iterator> iterators;

        for (auto it = nodes.begin(); it != nodes.end(); it++)
        {
            if (!it->second.second)
            {
                iterators.push_back(it);
            }
        }

        for (auto it : iterators)
        {
            nodes.erase(it);
        }
    }
}