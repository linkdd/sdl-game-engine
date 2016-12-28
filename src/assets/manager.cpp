#include <sge/assets/manager.hpp>

using namespace std;

namespace sge
{
    void SGEAssetManager::register_locator(SGEAssetLocator *locator)
    {
        locators.push_back(locator);
    }

    void SGEAssetManager::register_loader(SGEAssetLoader *loader, vector<string> const &extensions)
    {
        for (auto it = extensions.begin(); it != extensions.end(); it++)
        {
            loaders[*it] = loader;
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
