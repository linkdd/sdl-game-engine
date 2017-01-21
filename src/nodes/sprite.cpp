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

    void SpriteNode::set_sprite(const std::string &assetname)
    {
        ImageDescriptor d(assetname);

        if (sprite == nullptr)
        {
            sprite = engine.assets().load<Image>(d);
        }
        else if (sprite->descriptor()->name() != d.name())
        {
            sprite.reset();
            sprite = engine.assets().load<Image>(d);
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

            int w = sprite->asset()->w;
            int h = sprite->asset()->h;

            dest.x = pos.x - w / 2;
            dest.y = pos.y - h / 2;
            dest.w = w;
            dest.h = h;

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
