#include <sge/assets/loaders/font.hpp>

using namespace std;

namespace sge
{
    SGEFontDescriptor::SGEFontDescriptor(string const &assetname, int font_size) : SGEAssetDescriptor(assetname), font_size(font_size) {}

    virtual size_t SGEFontDescriptor::hash() const
    {
        return SGEAssetDescriptor::hash() ^ std::hash(font_size);
    }

    virtual bool SGEFontDescriptor::compare(const SGEAssetDescriptor *other) const
    {
        return SGEAssetDescriptor::compare(other) && (font_size == other->fontSize());
    }

    int SGEFontDescriptor::fontSize() const;

    virtual void SGEFontLoader::load(SGEFont *asset, SDL_RWops *input)
    {
        auto descriptor = dynamic_cast<SGEFontDescriptor *>(asset->descriptor());

        TTF_Font *content = TTF_OpenFontRW(input, 1, descriptor->fontSize());

        if (content == NULL)
        {
            throw SGEAssetLoaderError("TTF", TTF_GetError());
        }

        asset << content;
    }

    virtual void SGEFontLoader::unload(SGEFont *asset)
    {
        TTF_CloseFont(asset->asset());
    }
}
