#ifndef __SGE_ASSET_CACHE_HPP
#define __SGE_ASSET_CACHE_HPP

#include <sge/assets/asset.hpp>
#include <sge/assets/cache.hpp>

#include <unordered_map>

namespace sge
{
    struct SGEAssetHasher
    {
        size_t operator()(const SGEAssetDescriptor &key) const
        {
            return key.get_hash();
        }
    };

    class SGEAssetCache : public std::unordered_map<SGEAssetDescriptor, SGEBaseAsset *, SGEAssetHasher> {};
}

#endif /* __SGE_ASSET_CACHE_HPP */
