#include <sge/initializers/sdl-fonts.hpp>
#include <SDL/SDL.h>
#include <SDL/SDL_ttf.h>

namespace sge
{
    void SDLFontsInitializer::do_initialize()
    {
        if (TTF_Init() != 0)
        {
            throw SGEInitError("SDL_ttf", TTF_GetError());
        }
    }

    void SDLFontsInitializer::do_shutdown()
    {
        TTF_Quit();
    }
}
