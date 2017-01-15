#ifndef __SGE_MANIFOLD_HPP
#define __SGE_MANIFOLD_HPP

#include <sge/node.hpp>
#include <sge/physics/vector.hpp>
#include <SDL.h>

namespace sge
{
    struct Contact
    {
        Vector position;
        Vector normal;
        float penetration;
    };

    struct Manifold
    {
        std::shared_ptr<Node> a;
        std::shared_ptr<Node> b;
        std::vector<Contact> contacts;
    };
}

#endif /* __SGE_MANIFOLD_HPP */
