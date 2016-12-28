#ifndef __SGE_IMAGE_LOADER_HPP
#define __SGE_IMAGE_LOADER_HPP

#include <SDL_image.h>

#include <sge/assets/loader.hpp>

namespace sge
{
    class Image : public Asset<SDL_Surface *> {};

    class ImageDescriptor : public AssetDescriptor {};

    class ImageLoader : public AssetLoader
    {
        public:
            virtual void load(BaseAsset *asset, SDL_RWops *input);
            virtual void unload(BaseAsset *asset);
    };
}

#endif /* __SGE_IMAGE_LOADER_HPP */
