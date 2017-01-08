#ifndef __SGE_ASSET_CACHE_HPP
#define __SGE_ASSET_CACHE_HPP

#include <sge/assets/asset.hpp>
#include <sge/assets/cache.hpp>

#include <unordered_map>
#include <memory>

namespace sge
{
    struct AssetHasher
    {
        size_t operator()(std::shared_ptr<AssetDescriptor> const &key) const
        {
            return key->get_hash();
        }
    };

    struct AssetPred
    {
        bool operator()(std::shared_ptr<AssetDescriptor> const &a, std::shared_ptr<AssetDescriptor> const &b) const
        {
            return a->compare(*b);
        }
    };

    class AssetCache : public std::unordered_map<std::shared_ptr<AssetDescriptor>, std::weak_ptr<BaseAsset>, AssetHasher, AssetPred> {};
}

#endif /* __SGE_ASSET_CACHE_HPP */
