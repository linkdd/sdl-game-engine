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
    class SGEConfiguration
    {
        public:
            SGEConfiguration();

            std::string gets(std::string const &param, std::string const &_default = std::string()) const;
            int geti(std::string const &param, int _default = 0) const;
            bool getb(std::string const &param, bool _default = false) const;
            float getf(std::string const &param, float _default = 0.0) const;

            SGEConfiguration &set(std::string const &param, std::string const &value);
            SGEConfiguration &set(std::string const &param, int value);
            SGEConfiguration &set(std::string const &param, bool value);
            SGEConfiguration &set(std::string const &param, float value);

        private:
            std::unordered_map<std::string, std::string> kvdb;
    };

    class SGEngine
    {
        public:
            SGEngine(SGEConfiguration &configuration);
            ~SGEngine();

            SGEConfiguration &configuration();
            SGEStartup &startup();
            SGEMainLoop &mainloop();
            SGEActionManager &actions();
            SGEAssetManager &assets();
            SGESceneManager &scenes();

        private:
            SGEConfiguration _configuration;

            SGEStartup _startup;
            SDLInitializer _sdl_init;
            SDLImageInitializer _sdl_img_init;
            SDLFontsInitializer _sdl_fonts_init;
            SDLWindowInitializer _sdl_window_init;

            SGEMainLoop _mloop;
            SGEActionManager _amgr;
            SGESceneManager _scmgr;

            SGEAssetManager _assets;

            SGEFileLocator _asset_file_locator;

            SGEImageLoader _asset_image_loader;
            SGEFontLoader _asset_font_loader;
    };
}

#endif /* __SGE_ENGINE_HPP */
