#ifndef __SGE_NODE_HPP
#define __SGE_NODE_HPP

#include <sge/engine-forward.hpp>
#include <SDL.h>

#include <memory>
#include <string>
#include <list>

namespace sge
{
    class Node : public std::enable_shared_from_this<Node>
    {
        public:
            Node(std::string const &name);

            const char *get_name() const;

            std::shared_ptr<Node> get_root();
            std::shared_ptr<Node> get_parent();
            std::shared_ptr<Node> get_node(std::string const &path);
            void add_child(std::shared_ptr<Node> child, bool reparent = true);
            void remove_child(std::shared_ptr<Node> child, bool reparent = true);
            void reparent(std::shared_ptr<Node> parent, bool remove = true, bool add = true);

            bool has_input() const;
            void set_input(bool enabled);
            bool send_input(std::weak_ptr<Engine> engine, SDL_Event *event);
            virtual bool input(std::weak_ptr<Engine> engine, SDL_Event *event);

            bool has_process() const;
            void set_process(bool enabled);
            void send_process(std::weak_ptr<Engine> engine, Uint32 delta);
            virtual void process(std::weak_ptr<Engine> engine, Uint32 delta);

            bool has_draw() const;
            void set_draw(bool enabled);
            void send_draw(std::weak_ptr<Engine> engine);
            virtual void draw(std::weak_ptr<Engine> engine);

            void send_enter_tree(std::weak_ptr<Engine> engine);
            virtual void enter_tree(std::weak_ptr<Engine> engine);
            virtual void ready(std::weak_ptr<Engine> engine);

            void send_exit_tree(std::weak_ptr<Engine> engine);
            virtual void exit_tree(std::weak_ptr<Engine> engine);

        private:
            bool input_enabled;
            bool process_enabled;
            bool draw_enabled;

            std::string name;
            std::shared_ptr<Node> parent;
            std::list<std::shared_ptr<Node> > children;
    };
}

#endif /* __SGE_NODE_HPP */
