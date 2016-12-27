#include <sge/initializers/sdl.hpp>
#include <SDL/SDL.h>

namespace sge
{
    void SDLInitializer::do_initialize()
    {
        if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
        {
            throw SGEInitError("SDL", SDL_GetError());
        }
    }

    void SDLInitializer::do_shutdown()
    {
        SDL_Quit();
    }
}
