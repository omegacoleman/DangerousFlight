
#ifndef _EXPLODE_H_
#define _EXPLODE_H_

#include <SDL/SDL.h>

typedef struct
{
    int x, y;
    int tick_left;
} Explode;

void explode_init();
int explosive_at(int x, int y);
void blit_explode(SDL_Surface *target);

#endif

