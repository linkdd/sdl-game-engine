#include <sge/assets/manager.hpp>
#include <iostream>

using namespace std;

namespace sge
{
    void SGEAssetManager::register_locator(SGEAssetLocator *locator)
    {
        locators.push_back(locator);
    }

    void SGEAssetManager::register_loader(SGEAssetLoader *loader, string const &extension)
    {
        loaders[extension] = loader;
    }

    template <typename H, typename T>
    void SGEAssetManager::register_loader(SGEAssetLoader *loader, H extension, T... extensions)
    {
        register_loader(loader, extension);
        register_loader(loader, extensions...);
    }

    template <class A, class D>
    A *load(D &assetdesc)
    {
        static_assert(is_base_of<SGEBaseAsset, A>::value);
        static_assert(is_base_of<SGEAssetDescriptor, D>::value);

        D *descriptor = new D(assetdesc);
        A *asset = NULL;

        if (cache.find(descriptor) == cache.end())
        {
            SDL_RWops *input = NULL;

            for (auto it = locators.begin(); it != locators.end(); it++)
            {
                auto locator = *it;

                try
                {
                    input = locator->locate(descriptor->name());
                }
                catch (SGEAssetLocatorError const &e)
                {
                    cerr << "[SGEAssetLocatorError] " << e.what() << endl;
                    input = NULL;
                }

                if (input != NULL)
                {
                    break;
                }
            }

            if (input != NULL)
            {
                if (loaders.find(descriptor->extension()) != loaders.end())
                {
                    auto loader = loaders[descriptor->extension()];
                    asset = new A(descriptor);

                    try
                    {
                        loader->load(asset, input);
                    }
                    catch (SGEAssetLoaderError const &e)
                    {
                        cerr << "[SGEAssetLoaderError] " << e.what() << endl;
                        delete asset;
                        asset = NULL;
                    }

                    if (asset != NULL)
                    {
                        cache[descriptor] = asset;
                    }
                }
                else
                {
                    cerr << "[SGEAssetLoaderError] No loader found for extension: " << descriptor->extension() << endl;
                    delete asset;
                    asset = NULL;
                }
            }
        }
        else
        {
            asset = cache[descriptor];
        }

        if (asset != NULL)
        {
            asset->acquire();
        }
        else
        {
            delete descriptor;
        }

        return asset;
    }

    void SGEAssetManager::unload(SGEBaseAsset *asset)
    {
        if (asset->dispose())
        {
            if (cache.find(asset->descriptor()) != cache.end())
            {
                cache.erase(asset->descriptor());
            }

            auto loader = loaders[asset->descriptor()->extension()];
            loader->unload(asset);
            delete asset->descriptor();
            delete asset;
        }
    }
}
