
#ifndef _EXPLODE_H_
#define _EXPLODE_H_

#include <SDL/SDL.h>

typedef struct
{
    int x, y;
    int tick_left;
    int type;
} Explode;

void explode_init();
int explosive_at(int x, int y);
int fire_at(int x, int y);
int fire(int x, int y);
void blit_explode(SDL_Surface *target);
int hit_test(int x, int y);

#endif

