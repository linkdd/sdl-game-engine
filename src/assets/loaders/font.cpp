#include <sge/assets/loaders/font.hpp>

using namespace std;

namespace sge
{
    FontDescriptor::FontDescriptor(string const &assetname, int font_size) : AssetDescriptor(assetname), font_size(font_size) {}

    size_t FontDescriptor::get_hash() const
    {
        hash<int> hashfn;
        return AssetDescriptor::get_hash() ^ hashfn(font_size);
    }

    bool FontDescriptor::compare(AssetDescriptor const &other) const
    {
        auto descriptor = static_cast<FontDescriptor const &>(other);
        return AssetDescriptor::compare(other) && (font_size == descriptor.fontSize());
    }

    int FontDescriptor::fontSize() const
    {
        return font_size;
    }

    void FontLoader::load(shared_ptr<BaseAsset> asset, SDL_RWops *input)
    {
        shared_ptr<Font> font = static_pointer_cast<Font>(asset);
        auto descriptor = static_pointer_cast<FontDescriptor>(font->descriptor());

        TTF_Font *content = TTF_OpenFontRW(input, 1, descriptor->fontSize());

        if (content == nullptr)
        {
            throw AssetLoaderError("TTF", TTF_GetError());
        }

        font->setAsset(content);
    }

    void FontLoader::unload(BaseAsset *asset)
    {
        if (asset->loaded())
        {
            Font *font = static_cast<Font *>(asset);
            TTF_CloseFont(font->asset());
        }
    }
}
