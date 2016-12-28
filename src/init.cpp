#include <sge/init.hpp>

namespace sge
{
    Initializer::Initializer() : initialized(false), freed(false)
    {}

    void Initializer::initialize()
    {
        if (!initialized)
        {
            do_initialize();
            initialized = true;
        }
    }

    void Initializer::shutdown()
    {
        if (!freed)
        {
            do_shutdown();
            freed = true;
        }
    }

    bool Initializer::is_initialized() const
    {
        return initialized;
    }

    bool Initializer::is_freed() const
    {
        return freed;
    }

    void Startup::add_initializer(std::shared_ptr<Initializer> initializer)
    {
        initializers.push_back(std::move(initializer));
    }

    void Startup::initialize()
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

    void Startup::shutdown()
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
