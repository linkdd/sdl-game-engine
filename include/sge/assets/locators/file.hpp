#ifndef __SGE_FILE_LOCATOR_HPP
#define __SGE_FILE_LOCATOR_HPP

#include <sge/assets/locator.hpp>

namespace sge
{
    class FileLocator : public AssetLocator
    {
        public:
            FileLocator(const std::string &location);

            virtual SDL_RWops *locate(const std::string &assetname);

        private:
            std::string _location;
    };
}

#endif /* __SGE_FILE_LOCATOR_HPP */
