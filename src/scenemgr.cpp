#include <sge/scenemgr.hpp>

using namespace std;

namespace sge
{
    Scene::Scene() : root_node(nullptr) {}
    Scene::~Scene()
    {
        if (root_node != nullptr)
        {
            delete root_node;
        }
    }

    Node *Scene::get_root_node() const
    {
        return root_node;
    }

    SceneManager::SceneManager(Engine *engine) : current_scene(nullptr), engine(engine) {}

    SceneManager::~SceneManager()
    {
        if (current_scene != nullptr)
        {
            current_scene->unload(engine);
        }
    }

    void SceneManager::add_scene(string const &name, Scene *scene)
    {
        scenes[name] = scene;
    }

    void SceneManager::switch_to_scene(string const &name)
    {
        if (current_scene != nullptr)
        {
            if (current_scene->get_root_node() != nullptr)
            {
                current_scene->get_root_node()->send_exit_tree(engine);
            }

            current_scene->unload(engine);
        }

        current_scene = scenes[name];
        current_scene->load(engine);

        if (current_scene->get_root_node() != nullptr)
        {
            current_scene->get_root_node()->send_enter_tree(engine);
        }
    }

    bool SceneManager::event_handler(SDL_Event *event)
    {
        if (current_scene != nullptr && current_scene->get_root_node() != nullptr)
        {
            return current_scene->get_root_node()->send_input(engine, event);
        }

        return true;
    }

    void SceneManager::process_handler(Uint32 delta)
    {
        if (current_scene != nullptr && current_scene->get_root_node() != nullptr)
        {
            current_scene->get_root_node()->send_process(engine, delta);
        }
    }

    void SceneManager::draw_handler()
    {
        if (current_scene != nullptr && current_scene->get_root_node() != nullptr)
        {
            current_scene->get_root_node()->send_draw(engine);
        }
    }
}
