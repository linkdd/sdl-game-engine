#include <sge/assets/loaders/image.hpp>

namespace sge
{
    virtual void SGEImageLoader::load(SGEImage *asset, SDL_RWops *input)
    {
        auto descriptor = dynamic_cast<SGEImageDescriptor *>(asset->descriptor());

        SDL_Surface *content = IMG_Load_RW(input, 1);

        if (content == NULL)
        {
            throw SGEAssetLoaderError("IMG", IMG_GetError());
        }

        asset << content;
    }

    virtual void SGEImageLoader::unload(SGEImage *asset)
    {
        SDL_FreeSurface(asset->asset());
    }
}
