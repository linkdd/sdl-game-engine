#include <sge/actionmgr.hpp>

using namespace std;

namespace sge
{
    void SGEActionManager::register_keyboard_action(string const &name, SDL_Keycode key)
    {
        a_keyboard[name].push_back(key);
    }

    void SGEActionManager::register_mouse_action(string const &name, Uint8 button)
    {
        a_mouse[name].push_back(button);
    }

    void SGEActionManager::register_joystick_action(string const &name, Uint8 button)
    {
        a_joystick[name].push_back(button);
    }

    bool SGEActionManager::is_action_pressed(string const &name) const
    {
        return a_active[name];
    }

    bool SGEActionManager::is_action_released(string const &name) const
    {
        return !a_active[name];
    }

    bool SGEActionManager::event_handler(SGEMainLoop *mainloop, SDL_Event *event, void *unused)
    {
        switch (event->type)
        {
            case SDL_CONTROLLERBUTTONDOWN:
                for (auto it = a_joystick.begin(); it != a_joystick.end(); it++)
                {
                    string action = it->first;
                    Uint8 button = it->second;

                    if (button == event->button)
                    {
                        a_active[action] = true;
                    }
                }

                break;

            case SDL_CONTROLLERBUTTONUP:
                for (auto it = a_joystick.begin(); it != a_joystick.end(); it++)
                {
                    string action = it->first;
                    Uint8 button = it->second;

                    if (button == event->button)
                    {
                        a_active[action] = false;
                    }
                }

                break;

            case SDL_KEYDOWN:
                for (auto it = a_keyboard.begin(); it != a_keyboard.end(); it++)
                {
                    string action = it->first;
                    SDL_Keycode key = it->second;

                    if (key == event->keysym.sym)
                    {
                        a_active[action] = true;
                    }
                }

                break;

            case SDL_KEYUP:
                for (auto it = a_keyboard.begin(); it != a_keyboard.end(); it++)
                {
                    string action = it->first;
                    SDL_Keycode key = it->second;

                    if (key == event->keysym.sym)
                    {
                        a_active[action] = false;
                    }
                }

                break;

            case SDL_MOUSEBUTTONDOWN:
                for (auto it = a_mouse.begin(); it != a_mouse.end(); it++)
                {
                    string action = it->first;
                    Uint8 button = it->second;

                    if (button == event->button)
                    {
                        a_active[action] = true;
                    }
                }

                break;


            case SDL_MOUSEBUTTONUP:
                for (auto it = a_mouse.begin(); it != a_mouse.end(); it++)
                {
                    string action = it->first;
                    Uint8 button = it->second;

                    if (button == event->button)
                    {
                        a_active[action] = false;
                    }
                }

                break;

            default:
                break;
        }

        return true;
    }
}