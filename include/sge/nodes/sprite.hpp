#ifndef __SGE_SPRITE_NODE_HPP
#define __SGE_SPRITE_NODE_HPP

#include <sge/nodes/position.hpp>
#include <sge/assets/loaders/image.hpp>

namespace sge
{
    class SpriteNode : public PositionNode
    {
        public:
            ~SpriteNode();

            virtual std::vector<std::string> mro() const;

            void set_sprite(std::string const &assetname);

            virtual void ready();
            virtual void draw();

        private:
            Image *sprite;
    };
}

#endif /* __SGE_SPRITE_NODE_HPP */
