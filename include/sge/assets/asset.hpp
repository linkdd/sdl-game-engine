#ifndef __SGE_ASSET_HPP
#define __SGE_ASSET_HPP

#include <functional>
#include <string>

namespace sge
{
    class SGEAssetDescriptor
    {
        public:
            SGEAssetDescriptor(std::string const &assetname);

            virtual size_t get_hash() const;
            virtual bool compare(const SGEAssetDescriptor &other) const;

            std::string name() const;
            std::string extension() const;

        private:
            std::string assetname;
    };

    class SGEBaseAsset
    {
        public:
            SGEBaseAsset(SGEAssetDescriptor &assetdesc);

            SGEAssetDescriptor &descriptor() const;

            void acquire();
            bool dispose();

        private:
            int refcount;
            SGEAssetDescriptor &desc;
    };

    template <typename T>
    class SGEAsset : public SGEBaseAsset
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
    bool operator==(const sge::SGEAssetDescriptor &lhs, const sge::SGEAssetDescriptor &rhs);
}

#endif /* __SGE_ASSET_HPP */
