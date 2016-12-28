#ifndef __SGE_IMAGE_LOADER_HPP
#define __SGE_IMAGE_LOADER_HPP

#include <sge/assets/loader.hpp>
#include <SDL/SDL_image.h>

namespace sge
{
    class SGEImage : public SGEAsset<SDL_Surface *> {};

    class SGEImageDescriptor : public SGEAssetDescriptor {};

    class SGEImageLoader : public SGEAssetLoader
    {
        public:
            virtual void load(SGEBaseAsset *asset, SDL_RWops *input);
            virtual void unload(SGEBaseAsset *asset);
    };
}

#endif /* __SGE_IMAGE_LOADER_HPP */
