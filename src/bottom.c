

#include "global.h"

#include "bottom.h"
#include <math.h>
#include "SDL.h"

#define MIN(a,b) (((a)>(b))?(b):(a))
#define MAX(a,b) (((a)<(b))?(b):(a))

#define HOLE_R 50
#define Z_WEIGHT 0.1 // Don't touch unless you know what you're doing.
#define HOLE_ALPG 0.15

void create_bullet_hole(
SDL_Surface *dest, SDL_Surface *z, int tx, int ty)
{
    int x, y;
    if ( SDL_MUSTLOCK(dest) ) {
        if ( SDL_LockSurface(dest) < 0 ) {
            return;
        }
    }
    #define HOLE_BORDER_LEFT MAX(tx - HOLE_R, 0)
    #define HOLE_BORDER_RIGHT MIN(tx + HOLE_R, dest->w)
    #define HOLE_BORDER_TOP MAX(ty - HOLE_R, 0)
    #define HOLE_BORDER_BOTTOM MIN(ty + HOLE_R, dest->h)
    for (x = HOLE_BORDER_LEFT; x < HOLE_BORDER_RIGHT; x++) {
        for (y = HOLE_BORDER_TOP; y < HOLE_BORDER_BOTTOM; y++) {
            Uint8 zz;
            Uint8 r, g, b, alph;
            int dis;
            SDL_GetRGB(get_pixel(z, x, y), z->format, &zz,  &zz,  &zz);
            SDL_GetRGBA(
            get_pixel(dest, x, y), dest->format, &r, &g, &b, &alph);
            dis = sqrt((tx-x)*(tx-x) + (ty-y)*(ty-y));
            if (dis < 50)
            {
                int toburn;
                #define noneg(a) ((a)>0?(a):0)
                toburn = 
                noneg(HOLE_R - dis - zz * Z_WEIGHT)
                 * 255 / HOLE_R * HOLE_ALPG;
                r = (Uint8)noneg((int)r - toburn);
                g = (Uint8)noneg((int)g - toburn);
                b = (Uint8)noneg((int)b - toburn);
                #undef noneg
            }
            set_pixel(dest, x, y, SDL_MapRGBA(dest->format, r, g, b, alph));
        }
    }
    if (SDL_MUSTLOCK(dest)) {
        SDL_UnlockSurface(dest);
    }
}

void set_pixel_alpha(SDL_Surface *surface, 
int x, int y, Uint8 alpha)
{
    Uint32 color;
    color = get_pixel(surface, x, y);
    color &= 0xffffffff - surface->format->Amask;
    color |= alpha << surface->format->Ashift;
    set_pixel(surface, x, y, color);
}

Uint32 get_pixel(SDL_Surface *surface, int x, int y)
{
    int bpp = surface->format->BytesPerPixel;
    Uint8 *p = (Uint8 *)surface->pixels + y * surface->pitch + x * bpp;
    switch(bpp) {
        case 1:
            return *p;
        case 2:
            return *(Uint16 *)p;
        case 3:
            if(SDL_BYTEORDER == SDL_BIG_ENDIAN)
                return p[0] << 16 | p[1] << 8 | p[2];
            else
                return p[0] | p[1] << 8 | p[2] << 16;
            return 0;
        case 4:
            return *(Uint32 *)p;
        default:
            return 0;
    }
}

void set_pixel(SDL_Surface *surface, int x, int y, Uint32 dst)
{
    int bpp = surface->format->BytesPerPixel;
    Uint8 *p = (Uint8 *)surface->pixels + y * surface->pitch + x * bpp;
    switch(bpp) {
        case 1:
            *p = dst;
            break;
        case 2:
            *(Uint16 *)p = dst;
            break;
        case 3:
            if(SDL_BYTEORDER == SDL_BIG_ENDIAN) {
                p[0] = (dst >> 16) & 0xff;
                p[1] = (dst >> 8) & 0xff;
                p[2] = dst & 0xff;
            } else {
                p[0] = dst & 0xff;
                p[1] = (dst >> 8) & 0xff;
                p[2] = (dst >> 16) & 0xff;
            }
            break;
        case 4:
            *(Uint32 *)p = dst;
            break;
        default:
            break;
    }
}


