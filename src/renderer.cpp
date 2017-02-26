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

    bool Renderer::draw_with_target(DrawRequest req)
    {
        SDL_Texture *old_target = SDL_GetRenderTarget(renderer);
        Uint32 tgt_format = SDL_PIXELFORMAT_RGBA8888;
        int tgt_access = SDL_TEXTUREACCESS_TARGET;
        int tgt_w = 0;
        int tgt_h = 0;

        if (old_target == NULL)
        {
            SDL_RenderGetLogicalSize(renderer, &tgt_w, &tgt_h);

            if (tgt_w == 0 || tgt_h == 0)
            {
                if (SDL_GetRendererOutputSize(renderer, &tgt_w, &tgt_h) != 0)
                {
                    set_error("SDL: "s + SDL_GetError());
                    return false;
                }
            }
        }
        else
        {
            if (SDL_QueryTexture(old_target, &tgt_format, &tgt_access, &tgt_w, &tgt_h) != 0)
            {
                set_error("SDL: "s + SDL_GetError());
                return false;
            }
        }

        SDL_Texture *target = SDL_CreateTexture(renderer, tgt_format, tgt_access, tgt_w, tgt_h);
        bool success = true;

        if (target == NULL)
        {
            set_error("SDL: "s + SDL_GetError());
            return false;
        }
        else
        {
            if (SDL_SetRenderTarget(renderer, target) != 0)
            {
                set_error("SDL: "s + SDL_GetError());
                success = false;
            }
            else
            {
                success = req();

                if (SDL_SetRenderTarget(renderer, old_target) != 0)
                {
                    set_error("SDL: "s + SDL_GetError());
                    success = false;
                }
                else
                {
                    if (SDL_RenderCopy(renderer, target, NULL, NULL) != 0)
                    {
                        set_error("SDL: "s + SDL_GetError());
                        success = false;
                    }
                }
            }

            SDL_DestroyTexture(target);
        }

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

    bool Renderer::draw_filled_shape(const Shape &shape, const SDL_Color &color)
    {
        bool success = true;

        auto edges = shape.get_edges();
        int n = edges.size();

        Sint16 *vx = new Sint16[n];
        Sint16 *vy = new Sint16[n];

        for (int i = 0; i < n; i++)
        {
            vx[i] = edges[i].start.x;
            vy[i] = edges[i].start.y;
        }

        if (!filledPolygonRGBA(renderer, vx, vy, n, color.r, color.g, color.b, color.a) != 0)
        {
            set_error("SDL_gfx: filledPolygonRGBA() error");
            success = false;
        }

        delete[] vx;
        delete[] vy;

        return success;
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
