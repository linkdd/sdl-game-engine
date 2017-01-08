#include <sge/nodes/tilemap.hpp>
#include <sge/engine.hpp>

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

    void TileMapNode::set_tilemap(string const &assetname)
    {
        JSONDescriptor tmap_d(assetname);

        if (tilemap == nullptr)
        {
            tilemap = engine.assets().load<JSON, JSONDescriptor>(tmap_d);
        }
        else if (tilemap->descriptor()->name() != tmap_d.name())
        {
            tilemap.reset();
            tilemap = engine.assets().load<JSON, JSONDescriptor>(tmap_d);
        }

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

        SDL_Point pos = get_absolute_pos();
    }
}
