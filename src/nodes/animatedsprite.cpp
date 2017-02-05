#include <sge/nodes/animatedsprite.hpp>
#include <sge/engine.hpp>
#include <iostream>

using namespace nlohmann;
using namespace std;

namespace sge
{
    vector<string> AnimatedSpriteNode::mro() const
    {
        auto _mro = PositionNode::mro();
        _mro.push_back("AnimatedSpriteNode");
        return _mro;
    }

    void AnimatedSpriteNode::set_animation(const string &assetname)
    {
        JSONDescriptor info_d(assetname);

        if (info == nullptr)
        {
            info = engine.assets().load<JSON>(info_d);
        }
        else if (info->descriptor()->name() != info_d.name())
        {
            info.reset();
            info = engine.assets().load<JSON>(info_d);
        }

        if (info != nullptr)
        {
            string spritesheet_assetname = info->asset()["/spritesheet/resource"_json_pointer];
            ImageDescriptor spritesheet_d(spritesheet_assetname);

            if (spritesheet == nullptr)
            {
                spritesheet = engine.assets().load<Image>(spritesheet_d);
            }
            else if (spritesheet->descriptor()->name() != spritesheet_d.name())
            {
                spritesheet.reset();
                spritesheet = engine.assets().load<Image>(spritesheet_d);
            }
        }
    }

    void AnimatedSpriteNode::flip(SDL_RendererFlip flip)
    {
        _flip = (SDL_RendererFlip) (_flip | flip);
    }

    void AnimatedSpriteNode::ready()
    {
        current_frame = 0;
        elapsed = 0;

        set_process(true);
        set_draw(true);
    }

    void AnimatedSpriteNode::process(Uint32 delta)
    {
        if (info == nullptr || spritesheet == nullptr)
        {
            return;
        }

        int nframes = info->asset()["/nframes"_json_pointer];
        int rate = info->asset()["/rate"_json_pointer];

        elapsed += delta;

        if (elapsed >= (1000.0 / rate))
        {
            current_frame++;

            if (current_frame == nframes)
            {
                current_frame = 0;
            }

            elapsed = 0;
        }
    }

    void AnimatedSpriteNode::draw()
    {
        if (info == nullptr || spritesheet == nullptr)
        {
            return;
        }

        json &nfo = info->asset();
        SDL_Point pos = get_absolute_pos().as_point();
        float angle = get_absolute_rotation();

        ostringstream spath;
        spath << "/frames/" << current_frame;
        string path = spath.str();

        int sx = nfo[json::json_pointer(path + "/0")];
        int sy = nfo[json::json_pointer(path + "/1")];
        int sw = nfo["/spritesheet/width"_json_pointer];
        int sh = nfo["/spritesheet/height"_json_pointer];
        int ss = nfo["/spritesheet/spacing"_json_pointer];

        SDL_Rect src;
        src.x = sx * (sw + ss);
        src.y = sy * (sh + ss);
        src.w = sw;
        src.h = sh;

        SDL_Rect dest;
        dest.x = pos.x - sw / 2;
        dest.y = pos.y - sh / 2;
        dest.w = sw;
        dest.h = sh;

        if (!engine.renderer().draw_image(spritesheet, src, dest, angle, pos, _flip))
        {
            cerr << "[AnimatedSpriteNode][ERROR] " << engine.renderer().get_error() << endl;
        }
    }
}
