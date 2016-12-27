#ifndef __SGE_FONT_LOADER_HPP
#define __SGE_FONT_LOADER_HPP

#include <sge/assets/loader.hpp>
#include <SDL/SDL_ttf.h>

namespace sge
{
    class SGEFont : public SGEAsset<TTF_Font *> {};

    class SGEFontDescriptor : public SGEAssetDescriptor
    {
        public:
            SGEFontDescriptor(std::string const &assetname, int font_size);

            virtual size_t hash() const;
            virtual bool compare(const SGEAssetDescriptor *other) const;

            int fontSize() const;

        private:
            int font_size;
    };

    class SGEFontLoader : public SGEAssetLoader
    {
        public:
            virtual void load(SGEFont *asset, SDL_RWops *input);
            virtual void unload(SGEFont *asset);
    };
}

#endif /* __SGE_FONT_LOADER_HPP */
