#include <sge/assets/manager.hpp>

using namespace std;

namespace sge
{
    void AssetManager::register_locator(std::shared_ptr<AssetLocator> locator)
    {
        locators.push_back(std::move(locator));
    }

    void AssetManager::register_loader(std::shared_ptr<AssetLoader> loader, std::vector<string> const &extensions)
    {
        for (const auto &ext : extensions)
        {
            loaders[ext] = loader;
        }
    }

    void AssetManager::unload(BaseAsset *asset)
    {
        if (asset != nullptr && asset->dispose())
        {
            auto it = cache.find(asset->descriptor());

            if (it != cache.end())
            {
                cache.erase(it);
            }

            auto loader = loaders[asset->descriptor()->extension()];
            loader->unload(asset);
            delete asset;
        }
    }
}
