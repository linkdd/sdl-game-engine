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
            Node(std::string const &name, std::weak_ptr<Engine> engine);

            const char *get_name() const;

            std::shared_ptr<Node> get_root();
            std::shared_ptr<Node> get_parent();
            std::shared_ptr<Node> get_node(std::string const &path);
            void add_child(std::shared_ptr<Node> child, bool reparent = true);
            void remove_child(std::shared_ptr<Node> child, bool reparent = true);
            void reparent(std::shared_ptr<Node> parent, bool remove = true, bool add = true);

            bool has_input() const;
            void set_input(bool enabled);
            bool send_input(SDL_Event *event);
            virtual bool input(SDL_Event *event);

            bool has_process() const;
            void set_process(bool enabled);
            void send_process(Uint32 delta);
            virtual void process(Uint32 delta);

            bool has_draw() const;
            void set_draw(bool enabled);
            void send_draw();
            virtual void draw();

            void send_enter_tree();
            virtual void enter_tree();
            virtual void ready();

            void send_exit_tree();
            virtual void exit_tree();

            bool is_in_tree() const;

        private:
            bool input_enabled;
            bool process_enabled;
            bool draw_enabled;
            bool in_tree;

            std::string name;
            std::weak_ptr<Engine> engine;

            std::weak_ptr<Node> parent;
            std::list<std::shared_ptr<Node>> children;
    };
}

#endif /* __SGE_NODE_HPP */
