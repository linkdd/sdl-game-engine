#include <sge/engine.hpp>

using namespace std;

namespace sge
{
    Engine::Engine(Configuration &configuration)
        : _configuration(configuration),
          _sdl_init(make_shared<SDLInitializer>()),
          _sdl_img_init(make_shared<SDLImageInitializer>()),
          _sdl_fonts_init(make_shared<SDLFontsInitializer>()),
          _sdl_window_init(make_shared<SDLWindowInitializer>(
              configuration.geti("display/width", 640),
              configuration.geti("display/height", 480),
              configuration.getb("display/fullscreen", false),
              configuration.getb("display/resizable", false),
              configuration.gets("display/scale", "none")
          )),
          _mloop(configuration.geti("fps", 60)),
          _scmgr(*this),
          _pmgr(*this),
          _asset_file_locator(make_shared<FileLocator>(configuration.gets("assets/file/location", ""))),
          _asset_image_loader(make_shared<ImageLoader>()),
          _asset_font_loader(make_shared<FontLoader>()),
          _asset_json_loader(make_shared<JSONLoader>())
    {
        _startup.add_initializer(_sdl_init);
        _startup.add_initializer(_sdl_img_init);
        _startup.add_initializer(_sdl_fonts_init);
        _startup.add_initializer(_sdl_window_init);

        try
        {
            _startup.initialize();
        }
        catch(const InitError &e)
        {
            _startup.shutdown();
            throw e;
        }

        _renderer.set_renderer(_sdl_window_init->renderer());

        _assets.register_locator(_asset_file_locator);
        _assets.register_loader(_asset_font_loader, {"ttf"});
        _assets.register_loader(_asset_json_loader, {"json"});
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

        _mloop.queue_event_handler(SDL_QUIT, [&](SDL_Event *) { _mloop.quit(); return true; });
        _mloop.add_event_watcher([&](SDL_Event *evt) { return _amgr.event_handler(evt); });
        _mloop.add_event_watcher([&](SDL_Event *evt) { return _scmgr.event_handler(evt); });
        _mloop.queue_process_handler([&](Uint32 delta) { _scmgr.process_handler(delta); });
        _mloop.queue_process_handler([&](Uint32 delta) { _pmgr.process_handler(delta); });
        _mloop.queue_draw_handler([&]() { renderer().clear(); });
        _mloop.queue_draw_handler([&]() { _scmgr.draw_handler(); });
        _mloop.queue_draw_handler([&]() { renderer().present(); });
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

    PhysicManager &Engine::physics()
    {
        return _pmgr;
    }

    SDL_Window *Engine::window() const
    {
        return _sdl_window_init->window();
    }

    Renderer &Engine::renderer()
    {
        return _renderer;
    }
}
