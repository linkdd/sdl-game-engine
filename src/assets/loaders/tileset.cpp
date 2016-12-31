#include <sge/assets/loaders/tileset.hpp>

namespace sge
{
    void TileSet::setTileName(int x, int y, std::string const &tilename)
    {
        tiles[tilename] = std::make_pair(x, y);
    }

    SDL_Rect TileSet::at(int x, int y) const
    {
        auto d = std::static_pointer_cast<TileSetDescriptor>(descriptor());
        SDL_Rect result;

        result.x = x * d->tileSize();
        result.y = y * d->tileSize();
        result.w = d->tileSize();
        result.h = d->tileSize();

        return result;
    }

    SDL_Rect TileSet::at(std::string const &tilename) const
    {
        auto d = std::static_pointer_cast<TileSetDescriptor>(descriptor());
        SDL_Rect result = {0, 0, d->tileSize(), d->tileSize()};

        auto it = tiles.find(tilename);

        if (it != tiles.end())
        {
            result.x = it->second.first * d->tileSize();
            result.y = it->second.second * d->tileSize();
        }

        return result;
    }

    TileSetDescriptor::TileSetDescriptor(std::string const &assetname, int tile_size) : AssetDescriptor(assetname), tile_size(tile_size) {}

    size_t TileSetDescriptor::get_hash() const
    {
        std::hash<int> hashfn;
        return AssetDescriptor::get_hash() ^ hashfn(tile_size);
    }

    bool TileSetDescriptor::compare(AssetDescriptor const &other) const
    {
        auto descriptor = static_cast<TileSetDescriptor const &>(other);
        return AssetDescriptor::compare(other) && (tile_size == descriptor.tileSize());
    }

    int TileSetDescriptor::tileSize() const
    {
        return tile_size;
    }

    void TileSetLoader::load(BaseAsset *asset, SDL_RWops *input)
    {
        TileSet *tset = static_cast<TileSet *>(asset);

        SDL_Surface *content = IMG_Load_RW(input, 1);

        if (content == nullptr)
        {
            throw AssetLoaderError("IMG", IMG_GetError());
        }

        tset->setAsset(content);
    }

    void TileSetLoader::unload(BaseAsset *asset)
    {
        TileSet *tset = static_cast<TileSet *>(asset);
        SDL_FreeSurface(tset->asset());
    }
}
