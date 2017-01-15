#ifndef __SGE_PHYSIC_MANAGER_HPP
#define __SGE_PHYSIC_MANAGER_HPP

#include <sge/engine-forward.hpp>
#include <SDL.h>

namespace sge
{
    class PhysicManager
    {
        public:
            PhysicManager(Engine &engine);

            void process_handler(Uint32 delta);

        private:
            Engine &engine;
    };
}

#endif /* __SGE_PHYSIC_MANAGER_HPP */
