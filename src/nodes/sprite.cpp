#include <sge/nodes/sprite.hpp>
#include <sge/engine.hpp>
#include <iostream>

namespace sge
{
    SpriteNode::~SpriteNode()
    {
        auto pengine = engine.lock();

        if (sprite != nullptr)
        {
            pengine->assets().unload(sprite);
        }
    }

    std::vector<std::string> SpriteNode::mro() const
    {
        auto _mro = PositionNode::mro();
        _mro.push_back("SpriteNode");
        return _mro;
    }

    void SpriteNode::set_sprite(std::string const &assetname)
    {
        auto pengine = engine.lock();
        ImageDescriptor d(assetname);

        if (sprite == nullptr)
        {
            sprite = pengine->assets().load<Image, ImageDescriptor>(d);
        }
        else if (sprite->descriptor()->name() != d.name())
        {
            pengine->assets().unload(sprite);
            sprite = pengine->assets().load<Image, ImageDescriptor>(d);
        }
    }

    void SpriteNode::ready()
    {
        set_draw(true);
    }

    void SpriteNode::draw()
    {
        auto pengine = engine.lock();
        SDL_Texture *t = SDL_CreateTextureFromSurface(pengine->renderer(), sprite->asset());
        bool error = false;

        if (t != NULL)
        {
            SDL_Point pos = get_pos();
            SDL_Rect dest;

            dest.x = pos.x;
            dest.y = pos.y;
            dest.w = sprite->asset()->w;
            dest.h = sprite->asset()->h;

            if (SDL_RenderCopy(pengine->renderer(), t, NULL, &dest) != 0)
            {
                error = true;
            }

            SDL_DestroyTexture(t);
        }
        else
        {
            error = true;
        }

        if (error)
        {
            std::cerr << "[SpriteNode][ERROR] SDL: " << SDL_GetError() << std::endl;
        }
    }
}
