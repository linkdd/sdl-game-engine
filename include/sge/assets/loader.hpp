#ifndef __SGE_ASSET_LOADER_HPP
#define __SGE_ASSET_LOADER_HPP

#include <sge/assets/asset.hpp>
#include <sge/error.hpp>
#include <SDL/SDL.h>

namespace sge
{
    class SGEAssetLoaderError : public SGEException
    {
        using SGEException::SGEException;
    };

    class SGEAssetLoader
    {
        public:
            virtual void load(SGEBaseAsset *asset, SDL_RWops *input) = 0;
            virtual void unload(SGEBaseAsset *asset) = 0;
    };
}

#endif /* __SGE_ASSET_LOADER_HPP */
