#ifndef __SGE_SDL_MIXER_INIT_HPP
#define __SGE_SDL_MIXER_INIT_HPP

#include <sge/init.hpp>

namespace sge
{
    class SDLMixerInitializer : public Initializer
    {
        public:
            SDLMixerInitializer(int frequency, int channels, int chunksize);

            void do_initialize();
            void do_shutdown();

        private:
            bool lib_initialized{false};
            int frequency;
            int channels;
            int chunksize;
    };
}

#endif /* __SGE_SDL_MIXER_INIT_HPP */
