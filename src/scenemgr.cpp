#include <sge/engine.hpp>
#include <sge/scenemgr.hpp>

using namespace std;

namespace sge
{
    Scene::Scene() : root_node(nullptr) {}

    shared_ptr<Node> Scene::get_root_node() const
    {
        return root_node;
    }

    SceneManager::SceneManager(Engine &engine) : engine(engine), current_scene(nullptr) {}

    SceneManager::~SceneManager()
    {
        if (current_scene != nullptr)
        {
            current_scene->unload(engine);
        }
    }

    void SceneManager::add_scene(const string &name, shared_ptr<Scene> scene)
    {
        scenes[name] = scene;
    }

    void SceneManager::switch_to_scene(const string &name)
    {
        if (current_scene != nullptr)
        {
            if (current_scene->get_root_node() != nullptr)
            {
                current_scene->get_root_node()->send_exit_tree();
            }

            current_scene->unload(engine);
        }

        current_scene = scenes[name];
        current_scene->load(engine);

        if (current_scene->get_root_node() != nullptr)
        {
            current_scene->get_root_node()->send_enter_tree();
        }
    }

    shared_ptr<Node> SceneManager::get_scene_node()
    {
        shared_ptr<Node> result;

        if (current_scene != nullptr)
        {
            result = current_scene->get_root_node();
        }

        return result;
    }

    bool SceneManager::event_handler(SDL_Event *event)
    {
        if (current_scene != nullptr && current_scene->get_root_node() != nullptr)
        {
            return current_scene->get_root_node()->send_input(event);
        }

        return true;
    }

    void SceneManager::process_handler(Uint32 delta)
    {
        if (current_scene != nullptr && current_scene->get_root_node() != nullptr)
        {
            current_scene->get_root_node()->send_process(delta);
        }
    }

    void SceneManager::draw_handler()
    {
        if (current_scene != nullptr && current_scene->get_root_node() != nullptr)
        {
            current_scene->get_root_node()->send_draw();
        }
    }
}
