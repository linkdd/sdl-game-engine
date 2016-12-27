#ifndef __SGE_INIT_HPP
#define __SGE_INIT_HPP

#include <sge/error.hpp>
#include <list>

namespace sge
{
    class SGEInitializer
    {
        public:
            SGEInitializer();

            virtual void do_initialize() = 0;
            virtual void do_shutdown() = 0;

            void initialize();
            void shutdown();

            bool is_initialized() const;
            bool is_freed() const;

        private:
            bool initialized;
            bool freed;
    };

    class SGEInitError : public SGEException {};

    class SGEStartup
    {
        public:
            void add_initializer(SGEInitializer *initializer);

            void initialize();
            void shutdown();

        private:
            std::list<SGEInitializer *> initializers;
    };
}

#endif /* __SGE_INIT_HPP */
