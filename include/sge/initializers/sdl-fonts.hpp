#ifndef __SGE_SDL_FONTS_INIT_HPP
#define __SGE_SDL_FONTS_INIT_HPP

#include <sge/init.hpp>

namespace sge
{
    class SDLFontsInitializer : public SGEInitializer
    {
        public:
            void do_initialize();
            void do_shutdown();
    };
}

#endif /* __SGE_SDL_FONTS_INIT_HPP */
