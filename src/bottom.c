

#include "global.h"

#include "bottom.h"
#include "SDL.h"

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


