
#ifndef _SPRITE_H_
#define _SPRITE_H_

#include <SDL/SDL.h>

#define CONFIG_DIR "config"
#define RES_DIR "res"

typedef struct
{
    *SDL_Surface orig;
    *SDL_Surface spec;
    *SDL_Surface alph;
    *SDL_Surface z;
    *SDL_Surface curr;
} SuperBlitable;


#endif


