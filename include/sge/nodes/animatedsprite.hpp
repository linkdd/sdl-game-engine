#ifndef __SGE_ANIMATED_SPRITE_NODE_HPP
#define __SGE_ANIMATED_SPRITE_NODE_HPP

#include <sge/nodes/position.hpp>
#include <sge/assets/loaders/image.hpp>
#include <sge/assets/loaders/json.hpp>

namespace sge
{
    class AnimatedSpriteNode : public PositionNode
    {
        using PositionNode::PositionNode;

        public:
            virtual std::vector<std::string> mro() const;

            void set_animation(const std::string &assetname);

            virtual void ready();
            virtual void process(Uint32 delta);
            virtual void draw();

        private:
            int current_frame;
            Uint32 elapsed;
            std::shared_ptr<Image> spritesheet;
            std::shared_ptr<JSON> info;
    };
}

#endif /* __SGE_ANIMATED_SPRITE_NODE_HPP */
