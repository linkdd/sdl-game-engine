#ifndef __SGE_ASSET_MANAGER_HPP
#define __SGE_ASSET_MANAGER_HPP

#include <sge/assets/locator.hpp>
#include <sge/assets/loader.hpp>
#include <sge/assets/asset.hpp>
#include <sge/assets/cache.hpp>

#include <string>
#include <list>
#include <map>

namespace sge
{
    class SGEAssetManager
    {
        public:
            void register_locator(SGEAssetLocator *locator);

            void register_loader(SGEAssetLoader *loader, std::string const &extension);
            template <typename H, typename T>
            void register_loader(SGEAssetLoader *loader, H extension, T... extensions);

            template <class A, class D>
            A *load(D &assetdesc);

            void unload(SGEBaseAsset *asset);

        private:
            std::list<SGEAssetLocator *> locators;
            std::map<std::string, SGEAssetLoader *> loaders;

            SGEAssetCache cache;
    };
}

#endif /* __SGE_ASSET_MANAGER_HPP */
