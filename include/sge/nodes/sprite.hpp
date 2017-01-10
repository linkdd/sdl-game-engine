#ifndef __SGE_SPRITE_NODE_HPP
#define __SGE_SPRITE_NODE_HPP

#include <sge/nodes/position.hpp>
#include <sge/assets/loaders/image.hpp>

namespace sge
{
    class SpriteNode : public PositionNode
    {
        using PositionNode::PositionNode;

        public:
            virtual std::vector<std::string> mro() const;

            void set_sprite(const std::string &assetname);

            virtual void ready();
            virtual void draw();

        private:
            std::shared_ptr<Image> sprite;
    };
}

#endif /* __SGE_SPRITE_NODE_HPP */
