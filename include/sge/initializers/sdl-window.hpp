#ifndef __SGE_SDL_WINDOW_INIT_HPP
#define __SGE_SDL_WINDOW_INIT_HPP

#include <SDL.h>

#include <sge/init.hpp>

namespace sge
{
    class SDLWindowInitializer : public Initializer
    {
        public:
            SDLWindowInitializer(int width, int height, bool fullscreen, bool resizable);

            void do_initialize();
            void do_shutdown();

            SDL_Window *window() const;
            SDL_Renderer *renderer() const;

        private:
            int width;
            int height;
            bool fullscreen;
            bool resizable;

            SDL_Window *_window;
            SDL_Renderer *_renderer;
    };
}

#endif /* __SGE_SDL_WINDOW_INIT_HPP */
