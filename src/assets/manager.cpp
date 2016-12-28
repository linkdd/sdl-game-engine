#include <sge/assets/manager.hpp>

using namespace std;

namespace sge
{
    void SGEAssetManager::register_locator(std::shared_ptr<SGEAssetLocator> locator)
    {
        locators.push_back(std::move(locator));
    }

    void SGEAssetManager::register_loader(std::shared_ptr<SGEAssetLoader> loader, std::vector<string> const &extensions)
    {
        for (const auto &ext : extensions)
        {
            loaders[ext] = loader;
        }
    }

    void SGEAssetManager::unload(SGEBaseAsset *asset)
    {
        if (asset->dispose())
        {
            if (cache.find(asset->descriptor()) != cache.end())
            {
                cache.erase(asset->descriptor());
            }

            auto loader = loaders[asset->descriptor().extension()];
            loader->unload(asset);
            delete asset;
        }
    }
}
