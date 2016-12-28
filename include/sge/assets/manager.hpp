#ifndef __SGE_ASSET_MANAGER_HPP
#define __SGE_ASSET_MANAGER_HPP

#include <sge/assets/locator.hpp>
#include <sge/assets/loader.hpp>
#include <sge/assets/asset.hpp>
#include <sge/assets/cache.hpp>

#include <unordered_map>
#include <iostream>
#include <string>
#include <vector>
#include <list>

namespace sge
{
    class SGEAssetManager
    {
        private:
            std::list<SGEAssetLocator *> locators;
            std::unordered_map<std::string, SGEAssetLoader *> loaders;

            SGEAssetCache cache;

        public:
            void register_locator(SGEAssetLocator *locator);
            void register_loader(SGEAssetLoader *loader, std::vector<std::string> const &extensions);

            void unload(SGEBaseAsset *asset);

            template <class A, class D>
            A *load(D const &assetdesc)
            {
                static_assert(std::is_base_of<SGEBaseAsset, A>::value, "Supplied asset type does not inherit from SGEAsset");
                static_assert(std::is_base_of<SGEAssetDescriptor, D>::value, "Supplied descriptor type does not inherit from SGEAssetDescriptor");

                A *asset = nullptr;

                if (cache.find(assetdesc) == cache.end())
                {
                    SDL_RWops *input = nullptr;

                    for (auto it = locators.begin(); it != locators.end(); it++)
                    {
                        auto locator = *it;

                        try
                        {
                            input = locator->locate(assetdesc.name());
                        }
                        catch (SGEAssetLocatorError const &e)
                        {
                            std::cerr << "[SGEAssetLocatorError] " << e.what() << std::endl;
                            input = nullptr;
                        }

                        if (input != nullptr)
                        {
                            break;
                        }
                    }

                    if (input != nullptr)
                    {
                        if (loaders.find(assetdesc.extension()) != loaders.end())
                        {
                            auto loader = loaders[assetdesc.extension()];
                            asset = new A(assetdesc);

                            try
                            {
                                loader->load(asset, input);
                            }
                            catch (SGEAssetLoaderError const &e)
                            {
                                std::cerr << "[SGEAssetLoaderError] " << e.what() << std::endl;
                                delete asset;
                                asset = nullptr;
                            }

                            if (asset != nullptr)
                            {
                                cache[assetdesc] = asset;
                            }
                        }
                        else
                        {
                            std::cerr << "[SGEAssetLoaderError] No loader found for extension: " << assetdesc.extension() << std::endl;
                            delete asset;
                            asset = nullptr;
                        }
                    }
                }
                else
                {
                    asset = cache[assetdesc];
                }

                if (asset != nullptr)
                {
                    asset->acquire();
                }

                return asset;
            }
    };
}

#endif /* __SGE_ASSET_MANAGER_HPP */
