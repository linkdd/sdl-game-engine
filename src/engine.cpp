#include <sge/engine.hpp>
#include <iostream>
#include <sstream>

using namespace std;

namespace sge
{
    template <typename T>
    string to_string(T value)
    {
        ostringstream ss;
        ss << value;
        return ss.str();
    }

    string &SGEConfiguration::gets(string const &param, string const &_default = "") const
    {
        string result;

        if (kvdb.find(param) != kvdb.end())
        {
            result = kvdb.at(param);
        }
        else
        {
            result = _default;
        }

        return result;
    }

    int SGEConfiguration::geti(string const &param, int _default = 0) const
    {
        return stoi(gets(param, to_string<int>(_default)));
    }

    bool SGEConfiguration::getb(string const &param, bool _default = false) const
    {
        return bool(geti(param, to_string<int>(int(_default))));
    }

    float SGEConfiguraton::getf(string const &param, float _default = 0.0) const
    {
        return stof(gets(param, to_string<float>(_default)));
    }

    SGEConfiguration &SGEConfiguration::set(string const &param, string const &value)
    {
        kvdb[param] = value;
        return *this;
    }

    SGEConfiguration &SGEConfiguration::set(string const &param, int value)
    {
        return set(param, to_string<int>(value));
    }

    SGEConfiguration &SGEConfiguration::set(string const &param, bool value)
    {
        return set(param, int(value));
    }

    SGEConfiguration &SGEConfiguration::set(string const &param, float value)
    {
        return set(param, to_string<float>(value));
    }

    SGEngine::SGEngine(SGEConfiguration &configuration)
        : _configuration(configuration),
          _sdl_window_init(
              configuration.geti("display/width", 640),
              configuration.geti("display/height", 480),
              configuration.getb("display/fullscreen", false),
              configuration.getb("display/resizable", false)
          ),
          mainloop(configuration.geti("fps", 60)),
          _scmgr(*this),
          _asset_file_locator(configuration.gets("assets/file/location", ""))
    {
        _startup.add_initializer(&_sdl_init);
        _startup.add_initializer(&_sdl_img_init);
        _startup.add_initializer(&_sdl_fonts_init);
        _startup.add_initializer(&_sdl_window_init);

        try
        {
            _startup.initialize();
        }
        catch(SGEInitError const &e)
        {
            _startup.shutdown();
            throw e;
        }

        _asset.register_locator(&_asset_file_locator);
        _assets.register_loader(
            &_asset_image_loader,
            "png",
            "bmp",
            "jpg", "jpeg",
            "tga",
            "pnm", "pbm", "pgm", "ppm",
            "xpm",
            "xcf",
            "pcx",
            "gif",
            "tif", "tiff",
            "lbm", "iff"
        );
        _assets.register_loader(&_asset_font_loader, "ttf");

        _mloop.queue_event_handler(
            SDL_QUIT,
            [](SGEMainLoop *mloop, SDL_Event *evt, void *udata)
            {
                mloop->quit();
                return true;
            },
            NULL
        );

        _mloop.add_event_watcher(_amgr.event_handler, NULL);
        _mloop.add_event_watcher(_scmgr.event_handler, this);
        _mloop.add_process_handler(_scmgr.process_handler, this);
        _mloop.add_draw_handler(_scmgr.draw_handler, this);
    }

    SGEngine::~SGEngine()
    {
        _startup.shutdown();
    }

    SGEConfiguration &configuration() const
    {
        return _configuration;
    }

    SGEStartup &startup() const
    {
        return _startup;
    }

    SGEMainLoop &mainloop() const
    {
        return _mloop;
    }

    SGEActionManager &actions() const
    {
        return _amgr;
    }

    SGEAssetManager &assets() const
    {
        return _assets;
    }

    SGESceneManager &scenes() const
    {
        return _scmgr;
    }
}
