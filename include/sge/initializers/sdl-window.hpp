#ifndef __SGE_SDL_WINDOW_INIT_HPP
#define __SGE_SDL_WINDOW_INIT_HPP

#include <sge/init.hpp>
#include <SDL.h>
#include <string>

namespace sge
{
    class SDLWindowInitializer : public Initializer
    {
        public:
            SDLWindowInitializer(int width, int height, bool fullscreen, bool resizable, const std::string &scale);

            void do_initialize();
            void do_shutdown();

            SDL_Window *window() const;
            SDL_Renderer *renderer() const;

        private:
            int width;
            int height;
            bool fullscreen;
            bool resizable;
            std::string scale;

            SDL_Window *_window;
            SDL_Renderer *_renderer;
    };
}

#endif /* __SGE_SDL_WINDOW_INIT_HPP */
