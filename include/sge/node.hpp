#ifndef __SGE_NODE_HPP
#define __SGE_NODE_HPP

#include <sge/engine.hpp>
#include <string>
#include <list>

namespace sge
{
    class SGENode
    {
        public:
            SGENode(std::string const &name);
            ~SGENode();

            const char *get_name() const;

            SGENode *get_root() const;
            SGENode *get_parent() const;
            SGENode *get_node(std::string const &path) const;
            void add_child(SGENode *child, bool reparent = true);
            void remove_child(SGENode *child, bool reparent = true);
            void reparent(SGENode *parent, bool remove = true, bool add = true);

            bool has_input() const;
            void set_input(bool enabled);
            bool send_input(SGEngine &engine, SDL_Event *event);
            virtual bool input(SGEngine &engine, SDL_Event *event);

            bool has_process() const;
            void set_process(bool enabled);
            void send_process(SGEngine &engine, Uint32 delta);
            virtual void process(SGEngine &engine, Uint32 delta);

            bool has_draw() const;
            void set_draw(bool enabled);
            void send_draw(SGEngine &engine);
            virtual void draw(SGEngine &engine);

            void send_enter_tree(SGEngine &engine);
            virtual void enter_tree(SGEngine &engine);
            virtual void ready(SGEngine &engine);

            void send_exit_tree(SGEngine &engine);
            virtual void exit_tree(SGEngine &engine);

        private:
            bool input_enabled;
            bool process_enabled;
            bool draw_enabled;

            std::string name;
            SGENode *parent;
            std::list<SGENode *> children;
    };
}

#endif /* __SGE_NODE_HPP */
