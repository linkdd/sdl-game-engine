#include <sge/node.hpp>
#include <sstream>
#include <string>
#include <list>

using namespace std;

namespace sge
{
    Node::Node(string const &name) : name(name), parent(nullptr), input_enabled(false), process_enabled(false), draw_enabled(false) {}

    Node::~Node()
    {
        for (auto it = children.begin(); it != children.end(); it++)
        {
            Node *child = *it;
            delete child;
        }
    }

    const char *Node::get_name() const
    {
        return name.c_str();
    }

    Node *Node::get_root()
    {
        Node *root = this;

        while (root->get_parent() != nullptr)
        {
            root = root->get_parent();
        }

        return root;
    }

    Node *Node::get_parent()
    {
        return parent;
    }

    Node *Node::get_node(string const &path)
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
                Node *child = nullptr;

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

    void Node::add_child(Node *child, bool reparent)
    {
        children.push_back(child);

        if (reparent)
        {
            child->reparent(this, true, false);
        }
    }

    void Node::remove_child(Node *child, bool reparent)
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

    void Node::reparent(Node *newparent, bool remove, bool add)
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

    bool Node::has_input() const
    {
        return input_enabled;
    }

    void Node::set_input(bool enabled)
    {
        input_enabled = enabled;
    }

    bool Node::send_input(Engine *engine, SDL_Event *event)
    {
        bool result = true;

        if (has_input())
        {
            result = result && input(engine, event);
        }

        for (auto it = children.begin(); it != children.end(); it++)
        {
            Node *child = *it;

            result = result && child->send_input(engine, event);
        }

        return result;
    }

    bool Node::input(Engine *engine, SDL_Event *event) {}

    bool Node::has_process() const
    {
        return process_enabled;
    }

    void Node::set_process(bool enabled)
    {
        process_enabled = enabled;
    }

    void Node::send_process(Engine *engine, Uint32 delta)
    {
        if (has_process())
        {
            process(engine, delta);
        }

        for (auto it = children.begin(); it != children.end(); it++)
        {
            Node *child = *it;

            child->send_process(engine, delta);
        }
    }

    void Node::process(Engine *engine, Uint32 delta) {}

    bool Node::has_draw() const
    {
        return draw_enabled;
    }

    void Node::set_draw(bool enabled)
    {
        draw_enabled = enabled;
    }

    void Node::send_draw(Engine *engine)
    {
        if (has_draw())
        {
            draw(engine);
        }

        for (auto it = children.begin(); it != children.end(); it++)
        {
            Node *child = *it;

            child->send_draw(engine);
        }
    }

    void Node::draw(Engine *engine) {}

    void Node::send_enter_tree(Engine *engine)
    {
        enter_tree(engine);

        for (auto it = children.begin(); it != children.end(); it++)
        {
            Node *child = *it;

            child->send_enter_tree(engine);
        }

        ready (engine);
    }

    void Node::enter_tree(Engine *engine) {}
    void Node::ready(Engine *engine) {}

    void Node::send_exit_tree(Engine *engine)
    {
        for (auto it = children.begin(); it != children.end(); it++)
        {
            Node *child = *it;

            child->send_exit_tree(engine);
        }

        exit_tree(engine);
    }

    void Node::exit_tree(Engine *engine) {}
}
