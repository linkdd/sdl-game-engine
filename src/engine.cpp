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

    string SGEConfiguration::gets(string const &param, string const &_default) const
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

    int SGEConfiguration::geti(string const &param, int _default) const
    {
        return stoi(gets(param, to_string<int>(_default)));
    }

    bool SGEConfiguration::getb(string const &param, bool _default) const
    {
        return bool(geti(param, int(_default)));
    }

    float SGEConfiguration::getf(string const &param, float _default) const
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
          _mloop(configuration.geti("fps", 60)),
          _scmgr(this),
          _asset_file_locator(std::make_shared<SGEFileLocator>(configuration.gets("assets/file/location", ""))),
          _asset_image_loader(std::make_shared<SGEImageLoader>()),
          _asset_font_loader(std::make_shared<SGEFontLoader>())
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

        _assets.register_locator(_asset_file_locator);
        _assets.register_loader(
            _asset_image_loader,
            {
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
            }
        );
        _assets.register_loader(_asset_image_loader, {"ttf"});

        _mloop.queue_event_handler(
            SDL_QUIT,
            [&](SDL_Event *evt)
            {
                _mloop.quit();
                return true;
            }
        );

        _mloop.add_event_watcher(
            [&](SDL_Event *evt)
            {
                return _amgr.event_handler(evt);
            }
        );
        _mloop.add_event_watcher(
            [&](SDL_Event *evt)
            {
                return _scmgr.event_handler(evt);
            }
        );
        _mloop.queue_process_handler(
            [&](Uint32 delta)
            {
                _scmgr.process_handler(delta);
            }
        );
        _mloop.queue_draw_handler(
            [&]()
            {
                _scmgr.draw_handler();
            }
        );
    }

    SGEngine::~SGEngine()
    {
        _startup.shutdown();
    }

    SGEConfiguration &SGEngine::configuration()
    {
        return _configuration;
    }

    SGEStartup &SGEngine::startup()
    {
        return _startup;
    }

    SGEMainLoop &SGEngine::mainloop()
    {
        return _mloop;
    }

    SGEActionManager &SGEngine::actions()
    {
        return _amgr;
    }

    SGEAssetManager &SGEngine::assets()
    {
        return _assets;
    }

    SGESceneManager &SGEngine::scenes()
    {
        return _scmgr;
    }
}
