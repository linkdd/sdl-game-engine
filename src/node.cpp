#include <sge/node.hpp>
#include <sstream>
#include <string>
#include <list>

using namespace std;

namespace sge
{
    Node::Node(string const &name, weak_ptr<Engine> engine) : name(name), engine(engine), input_enabled(false), process_enabled(false), draw_enabled(false), in_tree(false) {}

    const char *Node::get_name() const
    {
        return name.c_str();
    }

    shared_ptr<Node> Node::get_root()
    {
        shared_ptr<Node> root = shared_from_this();

        while (root->get_parent() != nullptr)
        {
            root = root->get_parent();
        }

        return root;
    }

    shared_ptr<Node> Node::get_parent()
    {
        return parent.lock();
    }

    shared_ptr<Node> Node::get_node(string const &path)
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
                    return shared_from_this();
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
                shared_ptr<Node> child = nullptr;

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

    void Node::add_child(shared_ptr<Node> child, bool reparent)
    {
        children.push_back(std::move(child));

        if (reparent)
        {
            child->reparent(shared_from_this(), true, false);
        }
    }

    void Node::remove_child(shared_ptr<Node> child, bool reparent)
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

    void Node::reparent(shared_ptr<Node> newparent, bool remove, bool add)
    {
        if (remove && get_parent() != nullptr)
        {
            if (is_in_tree())
            {
                send_exit_tree();
            }

            get_parent()->remove_child(shared_from_this(), false);
        }

        parent = newparent;

        if (add && get_parent() != nullptr)
        {
            get_parent()->add_child(shared_from_this(), false);

            if (is_in_tree())
            {
                send_enter_tree();
            }
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

    bool Node::send_input(SDL_Event *event)
    {
        bool result = true;

        if (has_input())
        {
            result = result && input(event);
        }

        for (auto &child : children)
        {
            result = result && child->send_input(event);
        }

        return result;
    }

    bool Node::input(SDL_Event *event) {}

    bool Node::has_process() const
    {
        return process_enabled;
    }

    void Node::set_process(bool enabled)
    {
        process_enabled = enabled;
    }

    void Node::send_process(Uint32 delta)
    {
        if (has_process())
        {
            process(delta);
        }

        for (auto &child : children)
        {
            child->send_process(delta);
        }
    }

    void Node::process(Uint32 delta) {}

    bool Node::has_draw() const
    {
        return draw_enabled;
    }

    void Node::set_draw(bool enabled)
    {
        draw_enabled = enabled;
    }

    void Node::send_draw()
    {
        if (has_draw())
        {
            draw();
        }

        for (auto &child : children)
        {
            child->send_draw();
        }
    }

    void Node::draw() {}

    void Node::send_enter_tree()
    {
        enter_tree();

        for (auto &child : children)
        {
            child->send_enter_tree();
        }

        in_tree = true;

        ready ();
    }

    void Node::enter_tree() {}
    void Node::ready() {}

    void Node::send_exit_tree()
    {
        for (auto &child : children)
        {
            child->send_exit_tree();
        }

        exit_tree();

        in_tree = false;
    }

    void Node::exit_tree() {}

    bool Node::is_in_tree() const
    {
        return in_tree;
    }
}
