#include <sge/assets/asset.hpp>
#include <typeinfo>

using namespace std;

namespace sge
{
    SGEAssetDescriptor::SGEAssetDescriptor(string const &assetname) : assetname(assetname) {}

    virtual size_t SGEAssetDescriptor::hash() const
    {
        return std::hash(assetname);
    }

    virtual bool SGEAssetDescriptor::compare(const SGEAssetDescriptor *other) const
    {
        return (assetname == other->name());
    }

    string SGEAssetDescriptor::name() const
    {
        return assetname;
    }

    string SGEAssetDescriptor::extension() const
    {
        size_t found = assetname.rfind(".");
        string result("");

        if (found != string::npos)
        {
            result = assetname.substr(found);
        }

        return result;
    }

    SGEBaseAsset::SGEBaseAsset(SGEAssetDescriptor *assetdesc) : desc(assetdesc), refcount(0) {}

    SGEAssetDescriptor *SGEBaseAsset::descriptor() const
    {
        return desc;
    }

    void SGEBaseAsset::acquire()
    {
        refcount++;
    }

    bool SGEBaseAsset::dispose()
    {
        refcount--;
        return (refcount <= 0);
    }

    template <typename T>
    void SGEAsset::operator<<(T content)
    {
        _asset = content;
    }

    template <typename T>
    T &SGEAsset::asset() const
    {
        return _asset;
    }
}

inline bool operator==(const sge::SGEAssetDescriptor *&lhs, const sge::SGEAssetDescriptor *&rhs)
{
    return (typeid(*lhs) == typeid(*rhs)) && lhs->compare(rhs);
}