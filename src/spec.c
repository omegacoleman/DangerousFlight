
#include "global.h"


#include "SDL.h"
#include "spec.h"
#include "bottom.h"

void change_spec(SDL_Surface *src, SDL_Surface *new_spec)
{
    int x, y;
    if ( SDL_MUSTLOCK(src) ) {
        if ( SDL_LockSurface(src) < 0 ) {
            return;
        }
    }
    for (x = 0; x < src->w; x++) {
        for (y = 0; y < src->h; y++) {
            int nr, ng, nb, a;
            Uint8 sr, sg, sb;
            Uint8 nsr, nsg, nsb;
            SDL_GetRGB(get_pixel(src, x, y), src->format, &sr,  &sg,  &sb);
            SDL_GetRGB(get_pixel(new_spec, x, y), new_spec->format, &nsr,  &nsg,  &nsb);
            a = (nsr + nsg + nsb) / 3;
            nr = sr - a + nsr;
            ng = sg - a + nsg;
            nb = sb - a + nsb;
            #define check_byte(r) ((r > 0)?((r < 255)?r:255):0)
            nr = check_byte(nr);
            ng = check_byte(ng);
            nb = check_byte(nb);
            #undef check_byte
            set_pixel(src, x, y, SDL_MapRGB(src->format, nr, ng, nb));
        }
    }
    if ( SDL_MUSTLOCK(src) ) {
        SDL_UnlockSurface(src);
    }
}

void change_style(SDL_Surface *src, Uint32 style)
{
    Uint8 rm, gm, bm;
    int x, y;
    SDL_GetRGB(style, src->format, &rm, &gm, &bm);
    if ( SDL_MUSTLOCK(src) ) {
        if ( SDL_LockSurface(src) < 0 ) {
            return;
        }
    }
    for (x = 0; x < src->w; x++) {
        for (y = 0; y < src->h; y++) {
            Uint32 color;
            Uint8 r, g, b;
            int nr, ng, nb;
            color = get_pixel(src, x, y);
            SDL_GetRGB(color, src->format, &r, &g, &b);
            nr = r * rm / 255;
            ng = g * gm / 255;
            nb = b * bm / 255;
            #define check_byte(r) ((r > 0)?((r < 255)?r:255):0)
            nr = check_byte(nr);
            ng = check_byte(ng);
            nb = check_byte(nb);
            #undef check_byte
            color = SDL_MapRGB(src->format, (Uint8)nr, (Uint8)ng, (Uint8)nb);
            set_pixel(src, x, y, color);
        }
    }
    if ( SDL_MUSTLOCK(src) ) {
        SDL_UnlockSurface(src);
    }
}

