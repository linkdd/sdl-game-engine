#include <sge/initializers/sdl-window.hpp>

using namespace std;

namespace sge
{
    SDLWindowInitializer::SDLWindowInitializer(int width, int height, bool fullscreen, bool resizable, const string &scale)
        : width(width), height(height),
          fullscreen(fullscreen), resizable(resizable), scale(scale),
          _window(nullptr), _renderer(nullptr)
    {}

    void SDLWindowInitializer::do_initialize()
    {
        Uint32 flags = 0;

        if (fullscreen) flags |= SDL_WINDOW_FULLSCREEN_DESKTOP;
        if (resizable) flags |= SDL_WINDOW_RESIZABLE;

        if (SDL_CreateWindowAndRenderer(width, height, flags, &_window, &_renderer) != 0)
        {
            throw InitError("SDL", SDL_GetError());
        }

        if (!scale.empty() && scale != "none")
        {
            SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, scale.c_str());
            SDL_RenderSetLogicalSize(_renderer, width, height);
        }
    }

    void SDLWindowInitializer::do_shutdown()
    {
        if (_renderer != nullptr)
        {
            SDL_DestroyRenderer(_renderer);
        }

        if (_window != nullptr)
        {
            SDL_DestroyWindow(_window);
        }
    }

    SDL_Window *SDLWindowInitializer::window() const
    {
        return _window;
    }

    SDL_Renderer *SDLWindowInitializer::renderer() const
    {
        return _renderer;
    }
}
