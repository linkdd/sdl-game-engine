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
            void flip(SDL_RendererFlip flip);

            virtual void ready();
            virtual void process(Uint32 delta);
            virtual void draw();

        private:
            SDL_RendererFlip _flip{SDL_FLIP_NONE};
            int current_frame{0};
            Uint32 elapsed{0};
            std::shared_ptr<Image> spritesheet;
            std::shared_ptr<JSON> info;
    };
}

#endif /* __SGE_ANIMATED_SPRITE_NODE_HPP */
