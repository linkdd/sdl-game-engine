#include <sge/assets/loaders/json.hpp>
#include <iostream>

namespace sge
{
    void JSONLoader::load(BaseAsset *asset, SDL_RWops *input)
    {
        JSON *jdoc = static_cast<JSON *>(asset);

        Sint64 length = SDL_RWseek(input, 0, RW_SEEK_END);

        if (length < 0)
        {
            throw AssetLoaderError("SDL", "Cannot seek into stream");
        }

        SDL_RWseek(input, 0, RW_SEEK_SET);

        char *buffer = new char[length];
        SDL_RWread(input, buffer, length, 1);
        nlohmann::json j = nlohmann::json::parse(buffer);
        delete[] buffer;

        jdoc->setAsset(j);

        if (SDL_RWclose(input) != 0)
        {
            std::cerr << "[JSONLoader] [WARNING] " << SDL_GetError() << std::endl;
        }
    }

    void JSONLoader::unload(BaseAsset *asset)
    {
        ;
    }
}
