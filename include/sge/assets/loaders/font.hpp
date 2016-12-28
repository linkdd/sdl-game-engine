#ifndef __SGE_FONT_LOADER_HPP
#define __SGE_FONT_LOADER_HPP

#include <SDL_ttf.h>

#include <sge/assets/loader.hpp>

namespace sge
{
    class SGEFont : public SGEAsset<TTF_Font *> {};

    class SGEFontDescriptor : public SGEAssetDescriptor
    {
        public:
            SGEFontDescriptor(std::string const &assetname, int font_size);

            virtual size_t get_hash() const;
            virtual bool compare(const SGEFontDescriptor &other) const;

            int fontSize() const;

        private:
            int font_size;
    };

    class SGEFontLoader : public SGEAssetLoader
    {
        public:
            virtual void load(SGEBaseAsset *asset, SDL_RWops *input);
            virtual void unload(SGEBaseAsset *asset);
    };
}

#endif /* __SGE_FONT_LOADER_HPP */
