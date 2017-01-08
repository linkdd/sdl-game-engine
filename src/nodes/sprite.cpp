#include <sge/nodes/sprite.hpp>
#include <sge/engine.hpp>
#include <iostream>

namespace sge
{
    std::vector<std::string> SpriteNode::mro() const
    {
        auto _mro = PositionNode::mro();
        _mro.push_back("SpriteNode");
        return _mro;
    }

    void SpriteNode::set_sprite(std::string const &assetname)
    {
        ImageDescriptor d(assetname);

        if (sprite == nullptr)
        {
            sprite = engine.assets().load<Image, ImageDescriptor>(d);
        }
        else if (sprite->descriptor()->name() != d.name())
        {
            sprite.reset();
            sprite = engine.assets().load<Image, ImageDescriptor>(d);
        }
    }

    void SpriteNode::ready()
    {
        set_draw(true);
    }

    void SpriteNode::draw()
    {
        if (sprite == nullptr)
        {
            return;
        }

        SDL_Texture *t = SDL_CreateTextureFromSurface(engine.renderer(), sprite->asset());
        bool error = false;

        if (t != NULL)
        {
            SDL_Point pos = get_pos();
            SDL_Rect dest;

            dest.x = pos.x;
            dest.y = pos.y;
            dest.w = sprite->asset()->w;
            dest.h = sprite->asset()->h;

            if (SDL_RenderCopy(engine.renderer(), t, NULL, &dest) != 0)
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
