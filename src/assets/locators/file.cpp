#include <sge/assets/locators/file.hpp>
#include <algorithm>

using namespace std;

namespace sge
{
#ifdef _WIN32
    const char *SEPARATOR = "\\";
    const char *REPLACE = "/";
#else
    const char *SEPARATOR = "/";
    const char *REPLACE = "\\";
#endif

    SGEFileLocator::SGEFileLocator(string const &location)
    {
        if (location == "")
        {
            location = get_current_working_dir();
        }

        location = _location;
    }

    virtual SDL_RWops *SGEFileLocator::locate(string const &assetname)
    {
        string fullpath = _location + SEPARATOR + assetname;
        replace(fullpath.begin(), fullpath.end(), REPLACE, SEPARATOR);

        SDL_RWops *input = SDL_RWFromFile (fullpath.c_str(), "rb");

        if (input == NULL)
        {
            throw SGEAssetLocatorError("SDL", SDL_GetError());
        }

        return input;
    }
}

#endif /* __SGE_FILE_LOCATOR_HPP */
