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
            it->second = false;
        }

        auto root = engine.scenes().get_scene_node();
        mark(root);

        vector<map<shared_ptr<Node>, bool>::iterator> iterators;

        for (auto it = nodes.begin(); it != nodes.end(); it++)
        {
            if (!it->second)
            {
                iterators.push_back(it);
            }
        }

        for (auto it : iterators)
        {
            nodes.erase(it);
        }
    }

    void NodeManager::mark(shared_ptr<Node> root)
    {
        nodes[root] = true;

        for (auto child : root->get_children())
        {
            mark(child);
        }
    }
}