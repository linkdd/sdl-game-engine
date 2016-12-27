#include <sge/init.hpp>

namespace sge
{
    SGEInitializer::SGEInitializer() : initialized(false), freed(false)
    {}

    void SGEInitializer::initialize()
    {
        if (!initialized)
        {
            do_initialize();
            initialized = true;
        }
    }

    void SGEInitializer::shutdown()
    {
        if (!freed)
        {
            do_shutdown();
            freed = true;
        }
    }

    bool SGEInitializer::is_initialized() const
    {
        return initialized;
    }

    bool SGEInitializer::is_freed() const
    {
        return freed;
    }

    void SGEStartup::add_initializer(SGEInitializer *initializer)
    {
        initializers.push_back(initializer);
    }

    void SGEStartup::initialize()
    {
        for (auto it = initializers.begin(); it != initializers.end(); it++)
        {
            auto initializer = *it;

            if (!initializer->is_initialized())
            {
                initializer->initialize();
            }
        }
    }

    void SGEStartup::shutdown()
    {
        for (auto it = initializers.rbegin(); it != initializers.rend(); it++)
        {
            auto initializer = *it;

            if (initializer->is_initialized() && !initializer->is_freed())
            {
                initializer->shutdown();
            }
        }
    }
}
