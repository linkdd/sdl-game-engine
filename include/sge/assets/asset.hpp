#ifndef __SGE_ASSET_HPP
#define __SGE_ASSET_HPP

#include <sge/assets/loader-forward.hpp>

#include <functional>
#include <memory>
#include <string>

namespace sge
{
    class AssetDescriptor
    {
        public:
            AssetDescriptor(const std::string &assetname, bool binary = true);

            virtual size_t get_hash() const;
            virtual bool compare(const AssetDescriptor &other) const;

            const std::string &name() const;
            std::string extension() const;
            bool binary() const;

        private:
            std::string assetname;
            bool _binary;
    };

    class BaseAsset
    {
        public:
            BaseAsset(std::shared_ptr<AssetLoader> loader, std::shared_ptr<AssetDescriptor> assetdesc);

            std::shared_ptr<AssetLoader> loader();
            std::shared_ptr<AssetDescriptor> descriptor();

            bool loaded() const;

        protected:
            void setLoaded();

        private:
            std::shared_ptr<AssetLoader> _loader;
            std::shared_ptr<AssetDescriptor> desc;
            bool _loaded;

    };

    template <typename T>
    class Asset : public BaseAsset
    {
        using BaseAsset::BaseAsset;

        public:
            void setAsset(T content)
            {
                _asset = content;
                setLoaded();
            }

            T &asset()
            {
                return _asset;
            }

        private:
            T _asset;
    };
}

#endif /* __SGE_ASSET_HPP */
