#ifndef __SGE_ASSET_LOADER_HPP
#define __SGE_ASSET_LOADER_HPP

#include <sge/assets/asset.hpp>
#include <sge/error.hpp>

#include <SDL.h>

#include <memory>

namespace sge
{
    class AssetLoaderError : public Exception
    {
        using Exception::Exception;
    };

    class AssetLoader
    {
        public:
            virtual void load(std::shared_ptr<BaseAsset> asset, SDL_RWops *input) = 0;
            virtual void unload(BaseAsset *asset) = 0;
    };
}

#endif /* __SGE_ASSET_LOADER_HPP */
