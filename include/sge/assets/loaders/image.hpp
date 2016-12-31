#ifndef __SGE_IMAGE_LOADER_HPP
#define __SGE_IMAGE_LOADER_HPP

#include <sge/assets/loader.hpp>

#include <SDL.h>
#include <SDL_image.h>

namespace sge
{
    class Image : public Asset<SDL_Surface *>
    {
        using Asset::Asset;
    };

    class ImageDescriptor : public AssetDescriptor
    {
        using AssetDescriptor::AssetDescriptor;
    };

    class ImageLoader : public AssetLoader
    {
        public:
            virtual void load(BaseAsset *asset, SDL_RWops *input);
            virtual void unload(BaseAsset *asset);
    };
}

#endif /* __SGE_IMAGE_LOADER_HPP */
