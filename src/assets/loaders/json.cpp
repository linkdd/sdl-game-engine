#include <sge/assets/loaders/json.hpp>
#include <exception>
#include <iostream>
#include <cstring>

using namespace nlohmann;
using namespace std;

namespace sge
{
    void JSONLoader::load(shared_ptr<BaseAsset> asset, SDL_RWops *input)
    {
        shared_ptr<JSON> jdoc = static_pointer_cast<JSON>(asset);

        Sint64 length = SDL_RWseek(input, 0, RW_SEEK_END);

        if (length < 0)
        {
            throw AssetLoaderError("SDL", "Cannot seek into stream");
        }

        SDL_RWseek(input, 0, RW_SEEK_SET);

        char *buffer = new char[length];
        memset(buffer, 0, length);

        SDL_RWread(input, buffer, sizeof(char), length);
        json j;

        try
        {
            j = json::parse(buffer);
        }
        catch(const exception &e)
        {
            delete[] buffer;
            throw AssetLoaderError("JSON", e.what());
        }

        delete[] buffer;
        jdoc->setAsset(j);

        if (SDL_RWclose(input) != 0)
        {
            cerr << "[JSONLoader] [WARNING] " << SDL_GetError() << endl;
        }
    }

    void JSONLoader::unload(BaseAsset *asset)
    {
        ;
    }
}
