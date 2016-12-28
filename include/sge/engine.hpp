#ifndef __SGE_ENGINE_HPP
#define __SGE_ENGINE_HPP

#include <sge/init.hpp>
#include <sge/initializers/sdl.hpp>
#include <sge/initializers/sdl-image.hpp>
#include <sge/initializers/sdl-fonts.hpp>
#include <sge/initializers/sdl-window.hpp>

#include <sge/mainloop.hpp>
#include <sge/actionmgr.hpp>
#include <sge/scenemgr.hpp>

#include <sge/assets/manager.hpp>
#include <sge/assets/locators/file.hpp>
#include <sge/assets/loaders/image.hpp>
#include <sge/assets/loaders/font.hpp>

#include <unordered_map>
#include <string>

namespace sge
{
    class Configuration
    {
        public:
            Configuration();

            std::string gets(std::string const &param, std::string const &_default = std::string()) const;
            int geti(std::string const &param, int _default = 0) const;
            bool getb(std::string const &param, bool _default = false) const;
            float getf(std::string const &param, float _default = 0.0) const;

            Configuration &set(std::string const &param, std::string const &value);
            Configuration &set(std::string const &param, int value);
            Configuration &set(std::string const &param, bool value);
            Configuration &set(std::string const &param, float value);

        private:
            std::unordered_map<std::string, std::string> kvdb;
    };

    class Engine
    {
        public:
            Engine(Configuration &configuration);
            ~Engine();

            Configuration &configuration();
            Startup &startup();
            MainLoop &mainloop();
            ActionManager &actions();
            AssetManager &assets();
            SceneManager &scenes();

        private:
            Configuration _configuration;

            Startup _startup;
            SDLInitializer _sdl_init;
            SDLImageInitializer _sdl_img_init;
            SDLFontsInitializer _sdl_fonts_init;
            SDLWindowInitializer _sdl_window_init;

            MainLoop _mloop;
            ActionManager _amgr;
            SceneManager _scmgr;

            AssetManager _assets;

            std::shared_ptr<FileLocator> _asset_file_locator;
            std::shared_ptr<ImageLoader> _asset_image_loader;
            std::shared_ptr<FontLoader> _asset_font_loader;
    };
}

#endif /* __SGE_ENGINE_HPP */
