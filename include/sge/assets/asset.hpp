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

            T asset() const
            {
                return _asset;
            }

        private:
            T _asset;
    };
}

#endif /* __SGE_ASSET_HPP */
