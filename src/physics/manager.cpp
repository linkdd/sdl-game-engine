#include <sge/physics/manager.hpp>
#include <sge/physics/manifold.hpp>

#include <sge/nodes/collisionshape.hpp>
#include <sge/nodes/boundingbox.hpp>
#include <sge/nodes/body.hpp>

#include <sge/engine.hpp>

using namespace std;

namespace sge
{
    PhysicManager::PhysicManager(Engine &engine) : engine(engine) {}

    void PhysicManager::process_handler(Uint32 delta)
    {
        auto root_node = engine.scenes().get_scene_node();
        auto nodes = root_node->find_children_by_type({"BodyNode"});

        vector<Manifold> manifolds;

        for (auto node : nodes)
        {
            for (auto onode : nodes)
            {
                if (node != onode)
                {
                    auto a_bbnodes = node->find_children_by_type({"BoundingBoxNode"});
                    auto b_bbnodes = onode->find_children_by_type({"BoundingBoxNode"});

                    for (auto bbnode : a_bbnodes)
                    {
                        bool overlap = false;

                        auto a_bbnode = static_pointer_cast<BoundingBoxNode>(bbnode);
                        SDL_Point pos = a_bbnode->get_absolute_pos().as_point();
                        SDL_Point box = a_bbnode->get_box();

                        SDL_Rect a_absbox;
                        a_absbox.x = pos.x - box.x / 2;
                        a_absbox.y = pos.y - box.y / 2;
                        a_absbox.w = box.x;
                        a_absbox.h = box.y;

                        for (auto obbnode : b_bbnodes)
                        {
                            auto b_bbnode = static_pointer_cast<BoundingBoxNode>(obbnode);
                            SDL_Point opos = b_bbnode->get_absolute_pos().as_point();
                            SDL_Point obox = b_bbnode->get_box();

                            SDL_Rect b_absbox;
                            b_absbox.x = opos.x - obox.x / 2;
                            b_absbox.y = opos.y - obox.y / 2;
                            b_absbox.w = obox.x;
                            b_absbox.h = obox.y;

                            if (SDL_HasIntersection(&a_absbox, &b_absbox))
                            {
                                Manifold m;
                                m.a = node;
                                m.b = onode;
                                m.mtv = Vector(0, 0);

                                manifolds.push_back(m);
                                overlap = true;
                                break;
                            }
                        }

                        if (overlap)
                        {
                            break;
                        }
                    }
                }
            }
        }

        for (auto &manifold : manifolds)
        {
            auto a_snodes = manifold.a->find_children_by_type({"CollisionShapeNode"});
            auto b_snodes = manifold.b->find_children_by_type({"CollisionShapeNode"});
            bool collision = false;

            if (a_snodes.empty() || b_snodes.empty())
            {
                collision = true;
            }
            else
            {
                for (auto a_snode : a_snodes)
                {
                    auto a_shapenode = static_pointer_cast<CollisionShapeNode>(a_snode);
                    Shape a_s = a_shapenode->get_shape();

                    for (auto b_snode : b_snodes)
                    {
                        auto b_shapenode = static_pointer_cast<CollisionShapeNode>(b_snode);
                        Shape b_s = b_shapenode->get_shape();
                        Vector mtv;

                        if (a_s.overlap(b_s, mtv))
                        {
                            manifold.mtv = manifold.mtv + mtv;
                            collision = true;
                        }
                    }
                }
            }

            if (collision)
            {
                auto body = static_pointer_cast<BodyNode>(manifold.a);
                body->colliding(manifold);
            }
        }
    }
}
