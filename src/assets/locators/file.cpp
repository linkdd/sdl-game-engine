#include <SDL.h>

#include <sge/assets/locators/file.hpp>
#include <algorithm>

using namespace std;

namespace sge
{
#ifdef _WIN32
    const char SEPARATOR = '\\';
    const char REPLACE = '/';
#else
    const char SEPARATOR = '/';
    const char REPLACE = '\\';
#endif

    FileLocator::FileLocator(string const &location) : AssetLocator()
    {
        if (location.empty())
        {
            char *tmp = SDL_GetBasePath();

            if (tmp == nullptr)
            {
                _location = ".";
            }
            else
            {
                _location = tmp;
                _location = _location.substr(0, _location.length() - 1);
            }
        }
        else
        {
            _location = location;
        }
    }

    SDL_RWops *FileLocator::locate(string const &assetname)
    {
        string fullpath = _location + SEPARATOR + assetname;
        replace(fullpath.begin(), fullpath.end(), REPLACE, SEPARATOR);

        SDL_RWops *input = SDL_RWFromFile(fullpath.c_str(), "rb");

        if (input == nullptr)
        {
            throw AssetLocatorError("SDL", SDL_GetError());
        }

        return input;
    }
}
