#include <SDL.h>
#include <SDL_mixer.h>

#include <sge/initializers/sdl-mixer.hpp>

namespace sge
{
    const int MIX_INIT_EVERYTHING = MIX_INIT_FLAC | MIX_INIT_MOD | MIX_INIT_MP3 | MIX_INIT_OGG;
    
    SDLMixerInitializer::SDLMixerInitializer(int frequency, int channels, int chunksize)
        : frequency(frequency), channels(channels), chunksize(chunksize)
    {}

    void SDLMixerInitializer::do_initialize()
    {
        if ((Mix_Init(MIX_INIT_EVERYTHING) & MIX_INIT_EVERYTHING) != MIX_INIT_EVERYTHING)
        {
            throw InitError("SDL_mixer", Mix_GetError());
        }

        lib_initialized = true;

        if (Mix_OpenAudio(frequency, MIX_DEFAULT_FORMAT, channels, chunksize) != 0)
        {
            throw InitError("SDL_mixer", Mix_GetError());
        }
    }

    void SDLMixerInitializer::do_shutdown()
    {
        if (lib_initialized)
        {
            Mix_CloseAudio();
        }

        Mix_Quit();
    }
}
