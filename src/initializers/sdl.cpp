#include <sge/initializers/sdl.hpp>
#include <SDL.h>

namespace sge
{
    void SDLInitializer::do_initialize()
    {
        SDL_SetMainReady();

        if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
        {
            throw InitError("SDL", SDL_GetError());
        }
    }

    void SDLInitializer::do_shutdown()
    {
        SDL_Quit();
    }
}
