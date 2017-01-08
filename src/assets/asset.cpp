#include <sge/assets/asset.hpp>
#include <typeinfo>

using namespace std;

namespace sge
{
    AssetDescriptor::AssetDescriptor(string const &assetname) : assetname(assetname) {}

    size_t AssetDescriptor::get_hash() const
    {
        hash<string> hashfn;
        return hashfn(assetname);
    }

    bool AssetDescriptor::compare(AssetDescriptor const &other) const
    {
        return (assetname == other.name());
    }

    string AssetDescriptor::name() const
    {
        return assetname;
    }

    string AssetDescriptor::extension() const
    {
        size_t found = assetname.rfind(".");
        string result("");

        if (found != string::npos)
        {
            result = assetname.substr(found + 1);
        }

        return result;
    }

    BaseAsset::BaseAsset(shared_ptr<AssetLoader> loader, shared_ptr<AssetDescriptor> assetdesc)
        : _loader(loader), desc(assetdesc), _loaded(false)
    {}

    shared_ptr<AssetLoader> BaseAsset::loader()
    {
        return _loader;
    }

    void BaseAsset::setLoaded()
    {
        _loaded = true;
    }

    bool BaseAsset::loaded() const
    {
        return _loaded;
    }

    shared_ptr<AssetDescriptor> BaseAsset::descriptor()
    {
        return desc;
    }
}
