#ifndef __SGE_SCENE_MANAGER_HPP
#define __SGE_SCENE_MANAGER_HPP

#include <sge/engine-forward.hpp>
#include <sge/node.hpp>

#include <unordered_map>
#include <string>

namespace sge
{
    class SGEScene
    {
        public:
            SGEScene();
            ~SGEScene();

            virtual void load(SGEngine *engine) = 0;
            virtual void unload(SGEngine *engine) = 0;

            SGENode *get_root_node() const;

        private:
            SGENode *root_node;
    };

    class SGESceneManager
    {
        public:
            SGESceneManager(SGEngine *engine);
            ~SGESceneManager();

            void add_scene(std::string const &name, SGEScene *scene);
            void switch_to_scene(std::string const &name);

            bool event_handler(SDL_Event *event);
            void process_handler(Uint32 delta);
            void draw_handler();

        private:
            SGEngine *engine;
            SGEScene *current_scene;

            std::unordered_map<std::string, SGEScene *> scenes;
    };
}

#endif /* __SGE_SCENE_MANAGER_HPP */
