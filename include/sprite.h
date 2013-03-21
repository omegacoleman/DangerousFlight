
#ifndef _SPRITE_H_
#define _SPRITE_H_

#include "SDL.h"

typedef struct
{
    SDL_Surface *orig;
    SDL_Surface *spec;
    SDL_Surface *alph;
    SDL_Surface *z;
    SDL_Surface *curr;
} SuperBlitable;

void load_models();
SuperBlitable* get_model(char *name);
void super_blit(SuperBlitable *superb, SDL_Surface *dest, 
int x, int y, int angle);
void fast_blit(SuperBlitable *superb, SDL_Surface *dest, int x, int y);
void center_blit(SDL_Surface *tob, SDL_Surface *dest, int x, int y);

#endif


