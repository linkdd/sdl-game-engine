#include <sge/nodes/tilemap.hpp>
#include <sge/engine.hpp>
#include <iostream>

using namespace nlohmann;
using namespace std;

namespace sge
{
    vector<string> TileMapNode::mro() const
    {
        auto _mro = PositionNode::mro();
        _mro.push_back("TileMapNode");
        return _mro;
    }

    void TileMapNode::set_tilemap(const string &assetname)
    {
        JSONDescriptor tmap_d(assetname);

        if (tilemap == nullptr)
        {
            tilemap = engine.assets().load<JSON>(tmap_d);
        }
        else if (tilemap->descriptor()->name() != tmap_d.name())
        {
            tilemap.reset();
            tilemap = engine.assets().load<JSON>(tmap_d);
        }

        if (tilemap != nullptr)
        {
            string tileset_assetname = tilemap->asset()["/tileset/resource"_json_pointer];
            ImageDescriptor tset_d(tileset_assetname);

            if (tileset == nullptr)
            {
                tileset = engine.assets().load<Image, ImageDescriptor>(tset_d);
            }
            else if (tileset->descriptor() ->name() != tset_d.name())
            {
                tileset.reset();
                tileset = engine.assets().load<Image, ImageDescriptor>(tset_d);
            }
        }
    }

    SDL_Rect TileMapNode::get_viewport() const
    {
        return viewport;
    }

    void TileMapNode::set_viewport(SDL_Rect vport)
    {
        viewport = vport;
    }

    void TileMapNode::set_viewport(int x, int y, int w, int h)
    {
        viewport.x = x;
        viewport.y = y;
        viewport.w = w;
        viewport.h = h;
    }

    void TileMapNode::ready()
    {
        set_draw(true);
    }

    void TileMapNode::draw()
    {
        if (tilemap == nullptr || tileset == nullptr)
        {
            return;
        }

        SDL_Surface *tset = tileset->asset();
        json tmap = tilemap->asset();

        SDL_Texture *tex = SDL_CreateTextureFromSurface(engine.renderer(), tset);

        if (tex != NULL)
        {
            SDL_Point pos = get_absolute_pos();

            int mw = tmap["/map/width"_json_pointer];
            int mh = tmap["/map/height"_json_pointer];
            int tw = tmap["/tileset/width"_json_pointer];
            int th = tmap["/tileset/height"_json_pointer];
            int ts = tmap["/tileset/spacing"_json_pointer];

            for(int x = viewport.x; x < viewport.w && x < mw; x++)
            {
                for(int y = viewport.y; y < viewport.h && y < mh; y++)
                {
                    ostringstream spath;
                    spath << "/map/tiles/" << y << "/" << x;
                    string path = spath.str();

                    string tile = tmap[json::json_pointer(path)];

                    if (!tile.empty())
                    {
                        path = "/tiles/" + tile + "/0";
                        int tilex = tmap[json::json_pointer(path)];

                        path = "/tiles/" + tile + "/1";
                        int tiley = tmap[json::json_pointer(path)];

                        SDL_Rect src;
                        src.x = (tilex + ts) * tw;
                        src.y = (tiley + ts) * th;
                        src.w = tw;
                        src.h = th;

                        SDL_Rect dest;
                        dest.x = pos.x + x * tw;
                        dest.y = pos.y + y * th;
                        dest.w = tw;
                        dest.h = th;

                        SDL_RenderCopy(engine.renderer(), tex, &src, &dest);
                    }
                }
            }
        }
        else
        {
            cerr << "[TileMapNode][ERROR] SDL: " << SDL_GetError() << endl;
        }
    }
}
