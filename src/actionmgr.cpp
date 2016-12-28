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
                for (auto it = a_joystick.begin(); it != a_joystick.end(); it++)
                {
                    string action = it->first;
                    list<Uint8> button = it->second;

                    for (auto it = button.begin(); it != button.end(); it++)
                    {
                        if (*it == event->cbutton.button)
                        {
                            a_active[action] = true;
                            break;
                        }
                    }
                }

                break;

            case SDL_CONTROLLERBUTTONUP:
                for (auto it = a_joystick.begin(); it != a_joystick.end(); it++)
                {
                    string action = it->first;
                    list<Uint8> button = it->second;

                    for (auto it = button.begin(); it != button.end(); it++)
                    {
                        if (*it == event->cbutton.button)
                        {
                            a_active[action] = false;
                            break;
                        }
                    }
                }

                break;

            case SDL_KEYDOWN:
                for (auto it = a_keyboard.begin(); it != a_keyboard.end(); it++)
                {
                    string action = it->first;
                    list<SDL_Keycode> key = it->second;

                    for (auto it = key.begin(); it != key.end(); it++)
                    {
                        if (*it == event->key.keysym.sym)
                        {
                            a_active[action] = true;
                            break;
                        }
                    }
                }

                break;

            case SDL_KEYUP:
                for (auto it = a_keyboard.begin(); it != a_keyboard.end(); it++)
                {
                    string action = it->first;
                    list<SDL_Keycode> key = it->second;

                    for (auto it = key.begin(); it != key.end(); it++)
                    {
                        if (*it == event->key.keysym.sym)
                        {
                            a_active[action] = false;
                            break;
                        }
                    }
                }

                break;

            case SDL_MOUSEBUTTONDOWN:
                for (auto it = a_mouse.begin(); it != a_mouse.end(); it++)
                {
                    string action = it->first;
                    list<Uint8> button = it->second;

                    for (auto it = button.begin(); it != button.end(); it++)
                    {
                        if (*it == event->button.button)
                        {
                            a_active[action] = true;
                            break;
                        }
                    }
                }

                break;


            case SDL_MOUSEBUTTONUP:
                for (auto it = a_mouse.begin(); it != a_mouse.end(); it++)
                {
                    string action = it->first;
                    list<Uint8> button = it->second;

                    for (auto it = button.begin(); it != button.end(); it++)
                    {
                        if (*it == event->button.button)
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
