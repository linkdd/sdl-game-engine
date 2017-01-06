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

    BaseAsset::BaseAsset(std::shared_ptr<AssetDescriptor> assetdesc) : desc(assetdesc), refcount(0) {}

    std::shared_ptr<AssetDescriptor> BaseAsset::descriptor() const
    {
        return desc;
    }

    void BaseAsset::acquire()
    {
        refcount++;
    }

    bool BaseAsset::dispose()
    {
        refcount--;
        return (refcount <= 0);
    }
}
