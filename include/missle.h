
#ifndef _MISSLE_H_
#define _MISSLE_H_

#include "SDL.h"
#include "gear.h"
#include "sprite.h"

#define MT_NONE 0
#define MT_STATIC 5
#define MT_GEAROBJ 7

typedef struct
{
    int type;
    int x, y;
    GearObject *gear;
} MissleTarget;


typedef struct
{
    GearObject gear;
    int explode_tick_left;
    MissleTarget target;
} Missle;

void missle_init();
Missle *gen_missle(int x, int y);
int step_missle(Missle *missle);
void blit_missle(Missle *missle, SDL_Surface *dest);
void lock_gear(Missle *missle, GearObject * gear);
void lock_point(Missle *missle, int x, int y);

#endif
