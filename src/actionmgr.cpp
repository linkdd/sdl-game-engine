#include <sge/actionmgr.hpp>

using namespace std;

namespace sge
{
    void ActionManager::register_keyboard_action(string const &name, SDL_Keycode key)
    {
        a_keyboard[name].push_back(key);
    }

    void ActionManager::register_mouse_action(string const &name, Uint8 button)
    {
        a_mouse[name].push_back(button);
    }

    void ActionManager::register_joystick_action(string const &name, Uint8 button)
    {
        a_joystick[name].push_back(button);
    }

    bool ActionManager::is_action_pressed(string const &name) const
    {
        return a_active.at(name);
    }

    bool ActionManager::is_action_released(string const &name) const
    {
        return !a_active.at(name);
    }

    bool ActionManager::event_handler(SDL_Event *event)
    {
        switch (event->type)
        {
            case SDL_CONTROLLERBUTTONDOWN:
                for (auto &joy : a_joystick)
                {
                    string action = joy.first;
                    vector<Uint8> button = joy.second;

                    for (auto b : button)
                    {
                        if (b == event->cbutton.button)
                        {
                            a_active[action] = true;
                            break;
                        }
                    }
                }

                break;

            case SDL_CONTROLLERBUTTONUP:
                for (auto &joy : a_joystick)
                {
                    string action = joy.first;
                    vector<Uint8> button = joy.second;

                    for (auto &b : button)
                    {
                        if (b == event->cbutton.button)
                        {
                            a_active[action] = false;
                            break;
                        }
                    }
                }

                break;

            case SDL_KEYDOWN:
                for (auto &kbd : a_keyboard)
                {
                    string action = kbd.first;
                    vector<SDL_Keycode> keys = kbd.second;

                    for (auto &key : keys)
                    {
                        if (key == event->key.keysym.sym)
                        {
                            a_active[action] = true;
                            break;
                        }
                    }
                }

                break;

            case SDL_KEYUP:
                for (auto &kbd : a_keyboard)
                {
                    string action = kbd.first;
                    vector<SDL_Keycode> keys = kbd.second;

                    for (auto &key : keys)
                    {
                        if (key == event->key.keysym.sym)
                        {
                            a_active[action] = false;
                            break;
                        }
                    }
                }

                break;

            case SDL_MOUSEBUTTONDOWN:
                for (auto &mouse : a_mouse)
                {
                    string action = mouse.first;
                    vector<Uint8> button = mouse.second;

                    for (auto &b : button)
                    {
                        if (b == event->button.button)
                        {
                            a_active[action] = true;
                            break;
                        }
                    }
                }

                break;

            case SDL_MOUSEBUTTONUP:
                for (auto &mouse : a_mouse)
                {
                    string action = mouse.first;
                    vector<Uint8> button = mouse.second;

                    for (auto &b : button)
                    {
                        if (b == event->button.button)
                        {
                            a_active[action] = false;
                            break;
                        }
                    }
                }

                break;

            default:
                break;
        }

        return true;
    }
}
