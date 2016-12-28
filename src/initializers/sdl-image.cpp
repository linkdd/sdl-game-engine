#include <SDL.h>
#include <SDL_image.h>

#include <sge/initializers/sdl-image.hpp>

namespace sge
{
    const int IMG_INIT_EVERYTHING = IMG_INIT_JPG | IMG_INIT_PNG;

    void SDLImageInitializer::do_initialize()
    {
        if (IMG_Init(IMG_INIT_EVERYTHING) & IMG_INIT_EVERYTHING != IMG_INIT_EVERYTHING)
        {
            throw SGEInitError("SDL_image", IMG_GetError());
        }
    }

    void SDLImageInitializer::do_shutdown()
    {
        IMG_Quit();
    }
}
