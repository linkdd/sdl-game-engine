#ifndef __SGE_ASSET_MANAGER_HPP
#define __SGE_ASSET_MANAGER_HPP

#include <sge/assets/locator.hpp>
#include <sge/assets/loader.hpp>
#include <sge/assets/asset.hpp>
#include <sge/assets/cache.hpp>

#include <unordered_map>
#include <iostream>
#include <memory>
#include <string>
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
            void register_loader(std::shared_ptr<AssetLoader> loader, const std::vector<std::string> &extensions);

            template <typename A, typename D>
            std::shared_ptr<A> load(const D &assetdesc)
            {
                static_assert(std::is_base_of<BaseAsset, A>::value, "Supplied asset type does not inherit from Asset");
                static_assert(std::is_base_of<AssetDescriptor, D>::value, "Supplied descriptor type does not inherit from AssetDescriptor");

                auto passetdesc = std::make_shared<D>(assetdesc);
                std::shared_ptr<A> asset = nullptr;

                if (cache.find(passetdesc) == cache.end())
                {
                    SDL_RWops *input = nullptr;

                    for (auto &locator : locators)
                    {
                        try
                        {
                            input = locator->locate(passetdesc->name(), passetdesc->binary());
                        }
                        catch (const AssetLocatorError &e)
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

                            asset = std::shared_ptr<A>(
                                new A(loader, passetdesc),
                                [&](A *ptr_asset)
                                {
                                    BaseAsset *ptr_basset = static_cast<BaseAsset *>(ptr_asset);
                                    unload(ptr_basset);
                                }
                            );

                            try
                            {
                                loader->load(asset, input);
                            }
                            catch (const AssetLoaderError &e)
                            {
                                std::cerr << "[AssetLoaderError] " << e.what() << std::endl;
                                asset.reset();
                            }

                            if (asset != nullptr)
                            {
                                cache[passetdesc] = std::static_pointer_cast<BaseAsset>(asset);
                            }
                        }
                        else
                        {
                            std::cerr << "[AssetLoaderError] No loader found for extension: " << passetdesc->extension() << std::endl;
                        }
                    }
                    else
                    {
                        std::cerr << "[AssetLocatorError] Request asset not found by any locator: " << passetdesc->name() << std::endl;
                    }
                }
                else
                {
                    asset = std::static_pointer_cast<A>(cache[passetdesc].lock());
                }

                return asset;
            }

        private:
            void unload(BaseAsset *asset);
    };
}

#endif /* __SGE_ASSET_MANAGER_HPP */
