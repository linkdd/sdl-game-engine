#ifndef __SGE_ASSET_MANAGER_HPP
#define __SGE_ASSET_MANAGER_HPP

#include <sge/assets/locator.hpp>
#include <sge/assets/loader.hpp>
#include <sge/assets/asset.hpp>
#include <sge/assets/cache.hpp>

#include <iostream>
#include <memory>
#include <string>
#include <unordered_map>
#include <vector>

namespace sge
{
    class AssetManager
    {
        private:
            std::vector<std::shared_ptr<AssetLocator>> locators;
            std::unordered_map<std::string, std::shared_ptr<AssetLoader>> loaders;

            AssetCache cache;

        public:
            void register_locator(std::shared_ptr<AssetLocator> locator);
            void register_loader(std::shared_ptr<AssetLoader> loader, std::vector<std::string> const &extensions);

            void unload(BaseAsset *asset);

            template <typename A, typename D>
            A *load(D const &assetdesc)
            {
                static_assert(std::is_base_of<BaseAsset, A>::value, "Supplied asset type does not inherit from Asset");
                static_assert(std::is_base_of<AssetDescriptor, D>::value, "Supplied descriptor type does not inherit from AssetDescriptor");

                auto passetdesc = std::make_shared<D>(assetdesc);
                A *asset = nullptr;

                if (cache.find(passetdesc) == cache.end())
                {
                    SDL_RWops *input = nullptr;

                    for (auto &locator : locators)
                    {
                        try
                        {
                            input = locator->locate(passetdesc->name());
                        }
                        catch (AssetLocatorError const &e)
                        {
                            std::cerr << "[AssetLocatorError] " << e.what() << std::endl;
                            input = nullptr;
                        }

                        if (input != nullptr)
                        {
                            break;
                        }
                    }

                    if (input != nullptr)
                    {
                        if (loaders.find(passetdesc->extension()) != loaders.end())
                        {
                            auto loader = loaders[passetdesc->extension()];
                            asset = new A(passetdesc);

                            try
                            {
                                loader->load(asset, input);
                            }
                            catch (AssetLoaderError const &e)
                            {
                                std::cerr << "[AssetLoaderError] " << e.what() << std::endl;
                                delete asset;
                                asset = nullptr;
                            }

                            if (asset != nullptr)
                            {
                                cache[passetdesc] = static_cast<BaseAsset *>(asset);
                            }
                        }
                        else
                        {
                            std::cerr << "[AssetLoaderError] No loader found for extension: " << passetdesc->extension() << std::endl;
                            delete asset;
                            asset = nullptr;
                        }
                    }
                    else
                    {
                        std::cerr << "[AssetLocatorError] Request asset not found by any locator: " << passetdesc->name() << std::endl;
                    }
                }
                else
                {
                    asset = static_cast<A *>(cache[passetdesc]);
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
