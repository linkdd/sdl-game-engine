#ifndef __SGE_ACTION_MANAGER_HPP
#define __SGE_ACTION_MANAGER_HPP

#include <SDL.h>

#include <unordered_map>
#include <string>
#include <vector>

namespace sge
{
    class ActionManager
    {
        public:
            void register_keyboard_action(const std::string &name, SDL_Keycode key);
            void register_mouse_action(const std::string &name, Uint8 button);
            void register_joystick_action(const std::string &name, Uint8 button);

            bool is_action_pressed(const std::string &name);
            bool is_action_released(const std::string &name);

            bool event_handler(SDL_Event *event);

        private:
            std::unordered_map<std::string, std::vector<SDL_Keycode>> a_keyboard;
            std::unordered_map<std::string, std::vector<Uint8>> a_mouse;
            std::unordered_map<std::string, std::vector<Uint8>> a_joystick;

            std::unordered_map<std::string, bool> a_active;
    };
}

#endif /* __SGE_ACTION_MANAGER_HPP */
