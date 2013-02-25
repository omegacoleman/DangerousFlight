
#ifndef _MISSLE_H_
#define _MISSLE_H_

#include "gear.h"
#include "sprite.h"
#include <SDL/SDL.h>

typedef struct
{
    GearObject gear;
    int explode_tick_left;
} Missle;


void missle_init();
Missle *gen_missle(int x, int y);
int step_missle(Missle *missle);
void blit_missle(Missle *missle, SDL_Surface *dest);


#endif
