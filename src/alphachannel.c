
#include "global.h"


#include "alphachannel.h"
#include "SDL.h"
#include "bottom.h"

void z_cut(SDL_Surface *src, SDL_Surface *s_z, Uint8 tocut, Uint8 blur)
{
    Uint8 max, blur_lowest, blur_length;
    int x, y;
    max = (((int)tocut + (int)blur) < 255) ? (tocut + blur) : 255;
    blur_lowest = (tocut > blur) ? (tocut - blur) : 0;
    blur_length = max - blur_lowest;
    if (SDL_MUSTLOCK(src)) {
        if ( SDL_LockSurface(src) < 0 ) {
            return;
        }
    }
    for (x = 0; x < src->w; x++) {
        for (y = 0; y < src->h; y++) {
            Uint8 z;
            SDL_GetRGB(get_pixel(s_z, x, y), s_z->format, &z, &z, &z);
            if (z > blur_lowest) {
                if (z > max) {
                    set_pixel_alpha(src, x, y, 0);
                } else {
                    Uint8 garbage, alph;
                    int blured;
                    SDL_GetRGBA(get_pixel(src, x, y), src->format, &garbage, &garbage, &garbage, &alph);
                    blured = alph * (blur_length - z + blur_lowest) / blur_length;
                    set_pixel_alpha(src, x, y, (Uint8)blured);
                }
            }
        }
    }
    if (SDL_MUSTLOCK(src)) {
        SDL_UnlockSurface(src);
    }
}

void set_alpha_channel(SDL_Surface *src, SDL_Surface *s_alpha)
{
    int x, y;
    if ( SDL_MUSTLOCK(src) ) {
        if ( SDL_LockSurface(src) < 0 ) {
            return;
        }
    }
    for (x = 0; x < src->w; x++) {
        for (y = 0; y < src->h; y++) {
            char alph;
            SDL_GetRGB(get_pixel(s_alpha, x, y), s_alpha->format, &alph,  &alph,  &alph);
            set_pixel_alpha(src, x, y, alph);
        }
    }
    if ( SDL_MUSTLOCK(src) ) {
        SDL_UnlockSurface(src);
    }
}



