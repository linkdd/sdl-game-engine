#ifndef __SGE_FONT_LOADER_HPP
#define __SGE_FONT_LOADER_HPP

#include <sge/assets/loader.hpp>

#include <SDL.h>
#include <SDL_ttf.h>

namespace sge
{
    class Font : public Asset<TTF_Font *>
    {
        using Asset<TTF_Font *>::Asset;
    };

    class FontDescriptor : public AssetDescriptor
    {
        using AssetDescriptor::AssetDescriptor;

        public:
            FontDescriptor(std::string const &assetname, int font_size);

            virtual size_t get_hash() const;
            virtual bool compare(AssetDescriptor const &other) const;

            int fontSize() const;

        private:
            int font_size;
    };

    class FontLoader : public AssetLoader
    {
        public:
            virtual void load(std::shared_ptr<BaseAsset> asset, SDL_RWops *input);
            virtual void unload(BaseAsset *asset);
    };
}

#endif /* __SGE_FONT_LOADER_HPP */
