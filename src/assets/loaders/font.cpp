#include <sge/assets/loaders/font.hpp>

using namespace std;

namespace sge
{
    SGEFontDescriptor::SGEFontDescriptor(string const &assetname, int font_size) : SGEAssetDescriptor(assetname), font_size(font_size) {}

    size_t SGEFontDescriptor::get_hash() const
    {
        hash<int> hashfn;
        return SGEAssetDescriptor::get_hash() ^ hashfn(font_size);
    }

    bool SGEFontDescriptor::compare(const SGEFontDescriptor &other) const
    {
        return SGEAssetDescriptor::compare(other) && (font_size == other.fontSize());
    }

    int SGEFontDescriptor::fontSize() const
    {
        return font_size;
    }

    void SGEFontLoader::load(SGEBaseAsset *asset, SDL_RWops *input)
    {
        SGEFont *font = static_cast<SGEFont *>(asset);
        auto descriptor = static_cast<SGEFontDescriptor &>(font->descriptor());

        TTF_Font *content = TTF_OpenFontRW(input, 1, descriptor.fontSize());

        if (content == nullptr)
        {
            throw SGEAssetLoaderError("TTF", TTF_GetError());
        }

        font->setAsset(content);
    }

    void SGEFontLoader::unload(SGEBaseAsset *asset)
    {
        SGEFont *font = static_cast<SGEFont *>(asset);
        TTF_CloseFont(font->asset());
    }
}
