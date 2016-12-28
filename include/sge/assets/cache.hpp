#ifndef __SGE_ASSET_CACHE_HPP
#define __SGE_ASSET_CACHE_HPP

#include <sge/assets/asset.hpp>
#include <sge/assets/cache.hpp>

#include <unordered_map>

namespace sge
{
    struct AssetHasher
    {
        size_t operator()(const AssetDescriptor &key) const
        {
            return key.get_hash();
        }
    };

    class AssetCache : public std::unordered_map<AssetDescriptor, BaseAsset *, AssetHasher> {};
}

#endif /* __SGE_ASSET_CACHE_HPP */
