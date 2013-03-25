
#ifndef _SPRITE_H_
#define _SPRITE_H_

#include "SDL.h"

#define SB_CF_NORMAL 3
#define SB_CF_FAST 2
#define SB_CF_FIRST 0

typedef struct
{
    SDL_Surface *orig;
    SDL_Surface *spec;
    SDL_Surface *alph;
    SDL_Surface *z;
    SDL_Surface *curr;
    int curr_flag;
    Uint32 last_spec;
} SuperBlitable;

void load_models();
SuperBlitable* get_model(char *name);
void super_blit(SuperBlitable *superb, SDL_Surface *dest, 
int x, int y, int angle);
void fast_blit(SuperBlitable *superb, SDL_Surface *dest, int x, int y);
void center_blit(SDL_Surface *tob, SDL_Surface *dest, int x, int y);

#endif


