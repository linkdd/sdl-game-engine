#include <sge/assets/loaders/image.hpp>

namespace sge
{
    void SGEImageLoader::load(SGEBaseAsset *asset, SDL_RWops *input)
    {
        SGEImage *img = static_cast<SGEImage *>(asset);

        SDL_Surface *content = IMG_Load_RW(input, 1);

        if (content == nullptr)
        {
            throw SGEAssetLoaderError("IMG", IMG_GetError());
        }

        img->setAsset(content);
    }

    void SGEImageLoader::unload(SGEBaseAsset *asset)
    {
        SGEImage *img = static_cast<SGEImage *>(asset);
        SDL_FreeSurface(img->asset());
    }
}
