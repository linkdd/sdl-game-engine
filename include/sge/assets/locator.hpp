#ifndef __SGE_ASSET_LOCATOR_HPP
#define __SGE_ASSET_LOCATOR_HPP

#include <sge/error.hpp>

#include <SDL.h>
#include <string>

namespace sge
{
    class AssetLocatorError : public Exception
    {
        using Exception::Exception;
    };

    class AssetLocator
    {
        public:
            virtual SDL_RWops *locate(std::string const &assetname) = 0;
    };
}

#endif /* __SGE_ASSET_LOCATOR_HPP */
