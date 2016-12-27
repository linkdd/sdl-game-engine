#ifndef __SGE_ASSET_LOCATOR_HPP
#define __SGE_ASSET_LOCATOR_HPP

#include <sge/error.hpp>

#include <SDL/SDL.h>
#include <string>

namespace sge
{
    class SGEAssetLocatorError : public SGEException {};

    class SGEAssetLocator
    {
        public:
            virtual SDL_RWops *locate(std::string const &assetname) = 0;
    };
}

#endif /* __SGE_ASSET_LOCATOR_HPP */
