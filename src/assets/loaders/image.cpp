#include <sge/assets/loaders/image.hpp>

namespace sge
{
    void ImageLoader::load(BaseAsset *asset, SDL_RWops *input)
    {
        Image *img = static_cast<Image *>(asset);

        SDL_Surface *content = IMG_Load_RW(input, 1);

        if (content == nullptr)
        {
            throw AssetLoaderError("IMG", IMG_GetError());
        }

        img->setAsset(content);
    }

    void ImageLoader::unload(BaseAsset *asset)
    {
        Image *img = static_cast<Image *>(asset);
        SDL_FreeSurface(img->asset());
    }
}
