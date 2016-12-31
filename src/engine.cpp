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

    template <class T>
    void disable_deleter(T *ptr) {};

    string Configuration::gets(string const &param, string const &_default) const
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

    int Configuration::geti(string const &param, int _default) const
    {
        return stoi(gets(param, to_string<int>(_default)));
    }

    bool Configuration::getb(string const &param, bool _default) const
    {
        return bool(geti(param, int(_default)));
    }

    float Configuration::getf(string const &param, float _default) const
    {
        return stof(gets(param, to_string<float>(_default)));
    }

    Configuration &Configuration::set(string const &param, string const &value)
    {
        kvdb[param] = value;
        return *this;
    }

    Configuration &Configuration::set(string const &param, int value)
    {
        return set(param, to_string<int>(value));
    }

    Configuration &Configuration::set(string const &param, bool value)
    {
        return set(param, int(value));
    }

    Configuration &Configuration::set(string const &param, float value)
    {
        return set(param, to_string<float>(value));
    }

    Engine::Engine(Configuration &configuration)
        : _configuration(configuration),
          _sdl_init(std::make_shared<SDLInitializer>()),
          _sdl_img_init(std::make_shared<SDLImageInitializer>()),
          _sdl_fonts_init(std::make_shared<SDLFontsInitializer>()),
          _sdl_window_init(std::make_shared<SDLWindowInitializer>(
              configuration.geti("display/width", 640),
              configuration.geti("display/height", 480),
              configuration.getb("display/fullscreen", false),
              configuration.getb("display/resizable", false)
          )),
          _mloop(configuration.geti("fps", 60)),
          _scmgr(std::shared_ptr<Engine>(this, disable_deleter<Engine>)),
          _asset_file_locator(std::make_shared<FileLocator>(configuration.gets("assets/file/location", ""))),
          _asset_image_loader(std::make_shared<ImageLoader>()),
          _asset_font_loader(std::make_shared<FontLoader>()),
          _asset_tileset_loader(std::make_shared<TileSetLoader>())
    {
        _startup.add_initializer(_sdl_init);
        _startup.add_initializer(_sdl_img_init);
        _startup.add_initializer(_sdl_fonts_init);
        _startup.add_initializer(_sdl_window_init);

        try
        {
            _startup.initialize();
        }
        catch(InitError const &e)
        {
            _startup.shutdown();
            throw e;
        }

        _assets.register_locator(_asset_file_locator);
        _assets.register_loader(_asset_font_loader, {"ttf"});
        _assets.register_loader(_asset_tileset_loader, {"tset"});
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

        _mloop.queue_event_handler(SDL_QUIT, [&](SDL_Event *evt) { _mloop.quit(); return true; });
        _mloop.add_event_watcher([&](SDL_Event *evt) { return _amgr.event_handler(evt); });
        _mloop.add_event_watcher([&](SDL_Event *evt) { return _scmgr.event_handler(evt); });
        _mloop.queue_process_handler([&](Uint32 delta) { _scmgr.process_handler(delta); });
        _mloop.queue_draw_handler([&]() { SDL_RenderClear(renderer()); });
        _mloop.queue_draw_handler([&]() { _scmgr.draw_handler(); });
    }

    Engine::~Engine()
    {
        _startup.shutdown();
    }

    Configuration &Engine::configuration()
    {
        return _configuration;
    }

    Startup &Engine::startup()
    {
        return _startup;
    }

    MainLoop &Engine::mainloop()
    {
        return _mloop;
    }

    ActionManager &Engine::actions()
    {
        return _amgr;
    }

    AssetManager &Engine::assets()
    {
        return _assets;
    }

    SceneManager &Engine::scenes()
    {
        return _scmgr;
    }

    SDL_Window *Engine::window() const
    {
        return _sdl_window_init->window();
    }

    SDL_Renderer *Engine::renderer() const
    {
        return _sdl_window_init->renderer();
    }
}
