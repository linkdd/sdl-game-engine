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
        set_viewport(vport.x, vport.y, vport.w, vport.h);
    }

    void TileMapNode::set_viewport(int x, int y, int w, int h)
    {
        if (tilemap != nullptr)
        {
            json &tmap = tilemap->asset();

            int mw = tmap["/map/width"_json_pointer];
            int mh = tmap["/map/height"_json_pointer];
            int tw = tmap["/tileset/width"_json_pointer];
            int th = tmap["/tileset/height"_json_pointer];

            viewport.w = max(0, w);
            viewport.h = max(0, h);
            viewport.x = min(mw * tw - viewport.w, max(0, x));
            viewport.y = min(mh * th - viewport.h, max(0, y));
        }
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

        json &tmap = tilemap->asset();

        SDL_Point pos = get_absolute_pos().as_point();

        int mw = tmap["/map/width"_json_pointer];
        int mh = tmap["/map/height"_json_pointer];
        int tw = tmap["/tileset/width"_json_pointer];
        int th = tmap["/tileset/height"_json_pointer];
        int ts = tmap["/tileset/spacing"_json_pointer];

        SDL_Rect tileviewport;
        tileviewport.w = min(mw, viewport.w / tw + (viewport.w % tw ? 1 : 0));
        tileviewport.h = min(mh, viewport.h / th + (viewport.h % th ? 1 : 0));
        tileviewport.x = min(mw - tileviewport.w, max(0, viewport.x / tw));
        tileviewport.y = min(mh - tileviewport.h, max(0, viewport.y / th));

        for (int x = 0; x < tileviewport.w; x++)
        {
            for (int y = 0; y < tileviewport.h; y++)
            {
                ostringstream spath;
                spath << "/map/tiles/" << (y + tileviewport.y) << "/" << (x + tileviewport.x);
                string path = spath.str();

                string tile = tmap[json::json_pointer(path)];

                if (!tile.empty())
                {
                    path = "/tiles/" + tile + "/0";
                    int tilex = tmap[json::json_pointer(path)];

                    path = "/tiles/" + tile + "/1";
                    int tiley = tmap[json::json_pointer(path)];

                    SDL_Rect src;
                    src.x = tilex * (ts + tw);
                    src.y = tiley * (ts + th);
                    src.w = tw;
                    src.h = th;

                    SDL_Rect dest;
                    dest.x = pos.x + x * tw;
                    dest.y = pos.y + y * th;
                    dest.w = tw;
                    dest.h = th;

                    if (!engine.renderer().draw_image(tileset, src, dest))
                    {
                        cerr << "[TileMapNode][ERROR] " << engine.renderer().get_error() << endl; 
                    }
                }
            }
        }
    }
}
