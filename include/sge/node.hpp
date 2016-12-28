#ifndef __SGE_NODE_HPP
#define __SGE_NODE_HPP

#include <sge/engine-forward.hpp>
#include <SDL.h>
#include <string>
#include <list>

namespace sge
{
    class Node
    {
        public:
            Node(std::string const &name);
            ~Node();

            const char *get_name() const;

            Node *get_root();
            Node *get_parent();
            Node *get_node(std::string const &path);
            void add_child(Node *child, bool reparent = true);
            void remove_child(Node *child, bool reparent = true);
            void reparent(Node *parent, bool remove = true, bool add = true);

            bool has_input() const;
            void set_input(bool enabled);
            bool send_input(Engine *engine, SDL_Event *event);
            virtual bool input(Engine *engine, SDL_Event *event);

            bool has_process() const;
            void set_process(bool enabled);
            void send_process(Engine *engine, Uint32 delta);
            virtual void process(Engine *engine, Uint32 delta);

            bool has_draw() const;
            void set_draw(bool enabled);
            void send_draw(Engine *engine);
            virtual void draw(Engine *engine);

            void send_enter_tree(Engine *engine);
            virtual void enter_tree(Engine *engine);
            virtual void ready(Engine *engine);

            void send_exit_tree(Engine *engine);
            virtual void exit_tree(Engine *engine);

        private:
            bool input_enabled;
            bool process_enabled;
            bool draw_enabled;

            std::string name;
            Node *parent;
            std::list<Node *> children;
    };
}

#endif /* __SGE_NODE_HPP */
