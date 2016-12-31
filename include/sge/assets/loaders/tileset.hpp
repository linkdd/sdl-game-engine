#ifndef __SGE_TILESET_LOADER_HPP
#define __SGE_TILESET_LOADER_HPP

#include <sge/assets/loader.hpp>

#include <SDL.h>
#include <SDL_image.h>

#include <unordered_map>
#include <utility>
#include <string>

namespace sge
{
    class TileSet : public Asset<SDL_Surface *>
    {
        using Asset::Asset;

        public:
            void setTileName(int x, int y, std::string const &tilename);

            SDL_Rect at(int x, int y) const;
            SDL_Rect at(std::string const &tilename) const;

        private:
            std::unordered_map<std::string, std::pair<int, int>> tiles;
    };

    class TileSetDescriptor : public AssetDescriptor
    {
        using AssetDescriptor::AssetDescriptor;

        public:
            TileSetDescriptor(std::string const &assetname, int tile_size);

            virtual size_t get_hash() const;
            virtual bool compare(AssetDescriptor const &other) const;

            int tileSize() const;

        private:
            int tile_size;
    };

    class TileSetLoader : public AssetLoader
    {
        public:
            virtual void load(BaseAsset *asset, SDL_RWops *input);
            virtual void unload(BaseAsset *asset);
    };
}

#endif /* __SGE_TILESET_LOADER_HPP */
