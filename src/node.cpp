#include <sge/node.hpp>
#include <sstream>
#include <string>
#include <list>

using namespace std;

namespace sge
{
    SGENode::SGENode(string const &name) : name(name), parent(nullptr), input_enabled(false), process_enabled(false), draw_enabled(false) {}

    SGENode::~SGENode()
    {
        for (auto it = children.begin(); it != children.end(); it++)
        {
            SGENode *child = *it;
            delete child;
        }
    }

    const char *SGENode::get_name() const
    {
        return name.c_str();
    }

    SGENode *SGENode::get_root()
    {
        SGENode *root = this;

        while (root->get_parent() != nullptr)
        {
            root = root->get_parent();
        }

        return root;
    }

    SGENode *SGENode::get_parent()
    {
        return parent;
    }

    SGENode *SGENode::get_node(string const &path)
    {
        if (path[0] == '/')
        {
            return get_root()->get_node(path.substr(1));
        }
        else
        {
            size_t pos = path.find("/");
            string childpath = path.substr(0, pos);

            if (childpath == ".")
            {
                if (pos == string::npos)
                {
                    return this;
                }
                else
                {
                    return get_node(path.substr(pos + 1));
                }
            }
            else if (childpath == "..")
            {
                if (pos == string::npos)
                {
                    return get_parent();
                }
                else
                {
                    return get_parent()->get_node(path.substr(pos + 1));
                }
            }
            else
            {
                SGENode *child = nullptr;

                for (auto it = children.begin(); it != children.end(); it++)
                {
                    if ((*it)->get_name() == childpath)
                    {
                        child = *it;
                        break;
                    }
                }

                if (pos == string::npos)
                {
                    return child;
                }
                else
                {
                    return child->get_node(path.substr(pos + 1));
                }
            }
        }
    }

    void SGENode::add_child(SGENode *child, bool reparent)
    {
        children.push_back(child);

        if (reparent)
        {
            child->reparent(this, true, false);
        }
    }

    void SGENode::remove_child(SGENode *child, bool reparent)
    {
        for (auto it = children.begin(); it != children.end(); it++)
        {
            if (*it == child)
            {
                children.erase(it);
                break;
            }
        }

        if (reparent)
        {
            child->reparent(nullptr, false, true);
        }
    }

    void SGENode::reparent(SGENode *newparent, bool remove, bool add)
    {
        if (remove && parent != nullptr)
        {
            parent->remove_child(this, false);
        }

        parent = newparent;

        if (add && parent != nullptr)
        {
            parent->add_child(this, false);
        }
    }

    bool SGENode::has_input() const
    {
        return input_enabled;
    }

    void SGENode::set_input(bool enabled)
    {
        input_enabled = enabled;
    }

    bool SGENode::send_input(SGEngine *engine, SDL_Event *event)
    {
        bool result = true;

        if (has_input())
        {
            result = result && input(engine, event);
        }

        for (auto it = children.begin(); it != children.end(); it++)
        {
            SGENode *child = *it;

            result = result && child->send_input(engine, event);
        }

        return result;
    }

    bool SGENode::input(SGEngine *engine, SDL_Event *event) {}

    bool SGENode::has_process() const
    {
        return process_enabled;
    }

    void SGENode::set_process(bool enabled)
    {
        process_enabled = enabled;
    }

    void SGENode::send_process(SGEngine *engine, Uint32 delta)
    {
        if (has_process())
        {
            process(engine, delta);
        }

        for (auto it = children.begin(); it != children.end(); it++)
        {
            SGENode *child = *it;

            child->send_process(engine, delta);
        }
    }

    void SGENode::process(SGEngine *engine, Uint32 delta) {}

    bool SGENode::has_draw() const
    {
        return draw_enabled;
    }

    void SGENode::set_draw(bool enabled)
    {
        draw_enabled = enabled;
    }

    void SGENode::send_draw(SGEngine *engine)
    {
        if (has_draw())
        {
            draw(engine);
        }

        for (auto it = children.begin(); it != children.end(); it++)
        {
            SGENode *child = *it;

            child->send_draw(engine);
        }
    }

    void SGENode::draw(SGEngine *engine) {}

    void SGENode::send_enter_tree(SGEngine *engine)
    {
        enter_tree(engine);

        for (auto it = children.begin(); it != children.end(); it++)
        {
            SGENode *child = *it;

            child->send_enter_tree(engine);
        }

        ready (engine);
    }

    void SGENode::enter_tree(SGEngine *engine) {}
    void SGENode::ready(SGEngine *engine) {}

    void SGENode::send_exit_tree(SGEngine *engine)
    {
        for (auto it = children.begin(); it != children.end(); it++)
        {
            SGENode *child = *it;

            child->send_exit_tree(engine);
        }

        exit_tree(engine);
    }

    void SGENode::exit_tree(SGEngine *engine) {}
}
