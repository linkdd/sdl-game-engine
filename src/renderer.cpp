#include <sge/renderer.hpp>

using namespace std;

namespace sge
{
    void Renderer::set_renderer(SDL_Renderer *rdr)
    {
        renderer = rdr;
    }

    bool Renderer::clear()
    {
        if (SDL_RenderClear(renderer) != 0)
        {
            set_error("SDL: "s + SDL_GetError());
            return false;
        }

        return true;
    }

    void Renderer::present()
    {
        SDL_RenderPresent(renderer);
    }

    bool Renderer::draw_with_color(DrawRequest req, const SDL_Color &color)
    {
        bool success = true;
        SDL_Color prev;

        SDL_GetRenderDrawColor(renderer, &prev.r, &prev.g, &prev.b, &prev.a);
        SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);

        success = req();

        SDL_SetRenderDrawColor(renderer, prev.r, prev.g, prev.b, prev.a);

        return success;
    }

    bool Renderer::draw_point(const Vector &pos, const SDL_Color &color)
    {
        return draw_with_color(
            [&]()
            {
                if (SDL_RenderDrawPoint(renderer, pos.x, pos.y) != 0)
                {
                    set_error("SDL: "s + SDL_GetError());
                    return false;
                }

                return true;
            },
            color
        );
    }

    bool Renderer::draw_line(const Vector &start, const Vector &end, const SDL_Color &color)
    {
        return draw_with_color(
            [&]()
            {
                if (SDL_RenderDrawLine(renderer, start.x, start.y, end.x, end.y) != 0)
                {
                    set_error("SDL: "s + SDL_GetError());
                    return false;
                }

                return true;
            },
            color
        );
    }

    bool Renderer::draw_rect(const SDL_Rect &r, const SDL_Color &color)
    {
        return draw_with_color(
            [&]()
            {
                if (SDL_RenderDrawRect(renderer, &r) != 0)
                {
                    set_error("SDL: "s + SDL_GetError());
                    return false;
                }

                return true;
            },
            color
        );
    }

    bool Renderer::draw_filled_rect(const SDL_Rect &r, const SDL_Color &color)
    {
        return draw_with_color(
            [&]()
            {
                if (SDL_RenderFillRect(renderer, &r) != 0)
                {
                    set_error("SDL: "s + SDL_GetError());
                    return false;
                }

                return true;
            },
            color
        );
    }

    bool Renderer::draw_shape(const Shape &shape, const SDL_Color &color)
    {
        bool success = true;

        for (auto edge : shape.get_edges())
        {
            success &= draw_line(edge.start, edge.end, color);
        }

        return success;
    }

    bool Renderer::draw_filled_shape(const Shape &, const SDL_Color &)
    {
        // TODO
        return true;
    }

    bool Renderer::draw_image(shared_ptr<Image> asset, const SDL_Rect &dest)
    {
        SDL_Texture *t = SDL_CreateTextureFromSurface(renderer, asset->asset());
        bool success = true;

        if (t != NULL)
        {
            if (SDL_RenderCopy(renderer, t, NULL, &dest) != 0)
            {
                set_error("SDL: "s + SDL_GetError());
                success = false;
            }

            SDL_DestroyTexture(t);
        }
        else
        {
            set_error("SDL: "s + SDL_GetError());
            success = false;
        }

        return success;
    }

    bool Renderer::draw_image(shared_ptr<Image> asset, const SDL_Rect &src, const SDL_Rect &dest)
    {
        SDL_Texture *t = SDL_CreateTextureFromSurface(renderer, asset->asset());
        bool success = true;

        if (t != NULL)
        {
            if (SDL_RenderCopy(renderer, t, &src, &dest) != 0)
            {
                set_error("SDL: "s + SDL_GetError());
                success = false;
            }

            SDL_DestroyTexture(t);
        }
        else
        {
            set_error("SDL: "s + SDL_GetError());
            success = false;
        }

        return success;
    }

    bool Renderer::draw_image(shared_ptr<Image> asset, const SDL_Rect &dest, float angle, const SDL_Point &center, SDL_RendererFlip flip)
    {
        SDL_Texture *t = SDL_CreateTextureFromSurface(renderer, asset->asset());
        bool success = true;

        if (t != NULL)
        {
            if (SDL_RenderCopyEx(renderer, t, NULL, &dest, angle, &center, flip) != 0)
            {
                set_error("SDL: "s + SDL_GetError());
                success = false;
            }

            SDL_DestroyTexture(t);
        }
        else
        {
            set_error("SDL: "s + SDL_GetError());
            success = false;
        }

        return success;
    }

    bool Renderer::draw_image(shared_ptr<Image> asset, const SDL_Rect &src, const SDL_Rect &dest, float angle, const SDL_Point &center, SDL_RendererFlip flip)
    {
        SDL_Texture *t = SDL_CreateTextureFromSurface(renderer, asset->asset());
        bool success = true;

        if (t != NULL)
        {
            if (SDL_RenderCopyEx(renderer, t, &src, &dest, angle, &center, flip) != 0)
            {
                set_error("SDL: "s + SDL_GetError());
                success = false;
            }

            SDL_DestroyTexture(t);
        }
        else
        {
            set_error("SDL: "s + SDL_GetError());
            success = false;
        }

        return success;
    }

    bool Renderer::draw_text(shared_ptr<Font> asset, const string &text, const Vector &pos, const SDL_Color &color)
    {
        SDL_Surface *txt = TTF_RenderText_Blended(asset->asset(), text.c_str(), color);
        bool success = true;

        if (txt != NULL)
        {
            SDL_Texture *t = SDL_CreateTextureFromSurface(renderer, txt);

            if (t != NULL)
            {
                SDL_Rect dest;
                dest.x = pos.x;
                dest.y = pos.y;
                dest.w = txt->w;
                dest.h = txt->h;

                if (SDL_RenderCopy(renderer, t, NULL, &dest) != 0)
                {
                    set_error("SDL: "s + SDL_GetError());
                    success = false;
                }

                SDL_DestroyTexture(t);
            }
            else
            {
                set_error("SDL: "s + SDL_GetError());
                success = false;
            }

            SDL_FreeSurface(txt);
        }
        else
        {
            set_error("TTF: "s + TTF_GetError());
            success = false;
        }

        return success;
    }

    void Renderer::set_error(const string &text)
    {
        error = text;
    }

    string Renderer::get_error() const
    {
        return error;
    }
}
