#ifndef __SGE_TIMER_HPP
#define __SGE_TIMER_HPP

#include <SDL/SDL.h>

namespace sge
{
    class SGETimer
    {
        public:
            SGETimer() : ticks(0) {}

            void start()
            {
                ticks = SDL_GetTicks();
            }

            Uint32 get_ticks()
            {
                return SDL_GetTicks() - ticks;
            }

        private:
            Uint32 ticks;
    };
}

#endif /* __SGE_TIMER_HPP */
