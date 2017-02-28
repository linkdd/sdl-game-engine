#include <sge/renderer.hpp>
#include <iostream>
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
        SDL_BlendMode mode;

        SDL_GetRenderDrawBlendMode(renderer, &mode);
        SDL_GetRenderDrawColor(renderer, &prev.r, &prev.g, &prev.b, &prev.a);
        SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);

        success = req();

        SDL_SetRenderDrawColor(renderer, prev.r, prev.g, prev.b, prev.a);
        SDL_SetRenderDrawBlendMode(renderer, mode);

        return success;
    }

    bool Renderer::draw_with_target(DrawRequest req, float angle, const SDL_Point &rotcenter, SDL_RendererFlip flip)
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
                    if (SDL_RenderCopyEx(renderer, target, NULL, NULL, angle, &rotcenter, flip) != 0)
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

    bool Renderer::draw_rect(const SDL_Rect &r, float angle, const SDL_Color &color)
    {
        SDL_Point center;
        center.x = r.x + r.w / 2;
        center.y = r.y + r.h / 2;

        return draw_with_target(
            [&]()
            {
                return draw_rect(r, color);
            },
            angle,
            center,
            SDL_FLIP_NONE
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

    bool Renderer::draw_filled_rect(const SDL_Rect &r, float angle, const SDL_Color &color)
    {
        SDL_Point center;
        center.x = r.x + r.w / 2;
        center.y = r.y + r.h / 2;

        return draw_with_target(
            [&]()
            {
                return draw_filled_rect(r, color);
            },
            angle,
            center,
            SDL_FLIP_NONE
        );
    }

    bool Renderer::draw_circle(const Vector &center, int radius, const SDL_Color &color)
    {
        return draw_with_color(
            [&]()
            {
                if (circleRGBA(renderer, center.x, center.y, radius, color.r, color.g, color.b, color.a) != 0)
                {
                    set_error("SDL_gfx: circleRGBA()");
                    return false;
                }

                return true;
            },
            color
        );
    }

    bool Renderer::draw_filled_circle(const Vector &center, int radius, const SDL_Color &color)
    {
        return draw_with_color(
            [&]()
            {
                if (filledCircleRGBA(renderer, center.x, center.y, radius, color.r, color.g, color.b, color.a) != 0)
                {
                    set_error("SDL_gfx: filledCircleRGBA()");
                    return false;
                }

                return true;
            },
            color
        );
    }

    bool Renderer::draw_ellipse(const Vector &center, int hradius, int vradius, const SDL_Color &color)
    {
        return draw_ellipse(center, hradius, vradius, 0, SDL_FLIP_NONE, color);
    }

    bool Renderer::draw_ellipse(const Vector &center, int hradius, int vradius, float angle, const SDL_Color &color)
    {
        return draw_ellipse(center, hradius, vradius, angle, SDL_FLIP_NONE, color);
    }

    bool Renderer::draw_ellipse(const Vector &center, int hradius, int vradius, SDL_RendererFlip flip, const SDL_Color &color)
    {
        return draw_ellipse(center, hradius, vradius, 0, flip, color);
    }

    bool Renderer::draw_ellipse(const Vector &center, int hradius, int vradius, float angle, SDL_RendererFlip flip, const SDL_Color &color)
    {
        return draw_with_target(
            [&]()
            {
                return draw_with_color(
                    [&]()
                    {
                        if (!ellipseRGBA(renderer, center.x, center.y, hradius, vradius, color.r, color.g, color.b, color.a) != 0)
                        {
                            set_error("SDL_gfx: elipseRGBA()");
                            return false;
                        }
                    },
                    color
                );
            },
            angle,
            center.as_point(),
            flip
        );
    }

    bool Renderer::draw_filled_ellipse(const Vector &center, int hradius, int vradius, const SDL_Color &color)
    {
        return draw_filled_ellipse(center, hradius, vradius, 0, SDL_FLIP_NONE, color);
    }

    bool Renderer::draw_filled_ellipse(const Vector &center, int hradius, int vradius, float angle, const SDL_Color &color)
    {
        return draw_filled_ellipse(center, hradius, vradius, angle, SDL_FLIP_NONE, color);
    }

    bool Renderer::draw_filled_ellipse(const Vector &center, int hradius, int vradius, SDL_RendererFlip flip, const SDL_Color &color)
    {
        return draw_filled_ellipse(center, hradius, vradius, 0, flip, color);
    }

    bool Renderer::draw_filled_ellipse(const Vector &center, int hradius, int vradius, float angle, SDL_RendererFlip flip, const SDL_Color &color)
    {
        return draw_with_target(
            [&]()
            {
                return draw_with_color(
                    [&]()
                    {
                        if (!filledEllipseRGBA(renderer, center.x, center.y, hradius, vradius, color.r, color.g, color.b, color.a) != 0)
                        {
                            set_error("SDL_gfx: filledEllipseRGBA()");
                            return false;
                        }
                    },
                    color
                );
            },
            angle,
            center.as_point(),
            flip
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
        return draw_with_color(
            [&]()
            {
                bool success = true;

                auto edges = shape.get_edges();
                int n = edges.size();

                vector<Sint16> vx;
                vector<Sint16> vy;

                for (int i = 0; i < n; i++)
                {
                    vx.push_back(edges[i].start.x);
                    vy.push_back(edges[i].start.y);
                }

                if (filledPolygonRGBA(renderer, vx.data(), vy.data(), n, color.r, color.g, color.b, color.a) != 0)
                {
                    set_error("SDL_gfx: filledPolygonRGBA() error");
                    success = false;
                }

                return success;
            },
            color
        );
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
