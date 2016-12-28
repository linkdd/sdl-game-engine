#ifndef __SGE_ASSET_LOADER_HPP
#define __SGE_ASSET_LOADER_HPP

#include <sge/assets/asset.hpp>
#include <sge/error.hpp>
#include <SDL.h>

namespace sge
{
    class AssetLoaderError : public Exception
    {
        using Exception::Exception;
    };

    class AssetLoader
    {
        public:
            virtual void load(BaseAsset *asset, SDL_RWops *input) = 0;
            virtual void unload(BaseAsset *asset) = 0;
    };
}

#endif /* __SGE_ASSET_LOADER_HPP */
