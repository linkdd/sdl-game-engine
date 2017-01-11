#ifndef __SGE_JSON_LOADER_HPP
#define __SGE_JSON_LOADER_HPP

#include <sge/assets/loader.hpp>

#include <SDL.h>
#include <json.hpp>

namespace sge
{
    class JSON : public Asset<nlohmann::json>
    {
        using Asset<nlohmann::json>::Asset;
    };

    class JSONDescriptor : public AssetDescriptor
    {
        public:
            JSONDescriptor(const std::string &assetname);
    };

    class JSONLoader : public AssetLoader
    {
        public:
            virtual void load(std::shared_ptr<BaseAsset> asset, SDL_RWops *input);
            virtual void unload(BaseAsset *asset);
    };
}

#endif /* __SGE_JSON_LOADER_HPP */
