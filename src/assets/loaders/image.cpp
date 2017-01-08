#include <sge/assets/loaders/image.hpp>

using namespace std;

namespace sge
{
    void ImageLoader::load(shared_ptr<BaseAsset> asset, SDL_RWops *input)
    {
        shared_ptr<Image> img = static_pointer_cast<Image>(asset);

        SDL_Surface *content = IMG_Load_RW(input, 1);

        if (content == nullptr)
        {
            throw AssetLoaderError("IMG", IMG_GetError());
        }

        img->setAsset(content);
    }

    void ImageLoader::unload(BaseAsset *asset)
    {
        if (asset->loaded())
        {
            Image *img = static_cast<Image *>(asset);
            SDL_FreeSurface(img->asset());
        }
    }
}
