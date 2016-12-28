#ifndef __SGE_ASSET_HPP
#define __SGE_ASSET_HPP

#include <functional>
#include <string>

namespace sge
{
    class AssetDescriptor
    {
        public:
            AssetDescriptor(std::string const &assetname);

            virtual size_t get_hash() const;
            virtual bool compare(AssetDescriptor const &other) const;

            std::string name() const;
            std::string extension() const;

        private:
            std::string assetname;
    };

    class BaseAsset
    {
        public:
            BaseAsset(AssetDescriptor &assetdesc);

            AssetDescriptor &descriptor() const;

            void acquire();
            bool dispose();

        private:
            int refcount;
            AssetDescriptor &desc;
    };

    template <typename T>
    class Asset : public BaseAsset
    {
        public:
            void setAsset(T content)
            {
                _asset = content;
            }

            T asset() const
            {
                return _asset;
            }

        private:
            T _asset;
    };
}

namespace std
{
    bool operator==(const sge::AssetDescriptor &lhs, const sge::AssetDescriptor &rhs);
}

#endif /* __SGE_ASSET_HPP */
