#include <sge/engine.hpp>
#include <sge/scenemgr.hpp>

using namespace std;

namespace sge
{
    Scene::Scene() : root_node(nullptr) {}

    std::shared_ptr<Node> Scene::get_root_node() const
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

    void SceneManager::add_scene(string const &name, shared_ptr<Scene> scene)
    {
        scenes[name] = std::move(scene);
    }

    void SceneManager::switch_to_scene(string const &name)
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
