
#include <stdlib.h>
#include "explode.h"
#include "sprite.h"

#define EX_TICK_FULL 10
#define EX_TICK_UNUSED -1
#define EX_NR_MAX 32
#define EX_FRAME_NR 10
#define EX_MODEL_NAME "explode_%d"

Explode explodes[EX_NR_MAX];
SuperBlitable *explode_frames[EX_FRAME_NR];

void explode_init()
{
    int i = 0;
    for (i = 0; i < EX_NR_MAX; i++)
    {
        explodes[i].tick_left = EX_TICK_UNUSED;
    }
    for (i = 1; i <= EX_FRAME_NR; i++)
    {
        char mname[255];
        sprintf(mname, EX_MODEL_NAME, i);
        explode_frames[i - 1] = get_model(mname);
    }
}

int explosive_at(int x, int y)
{
    int i = 0;
    for (i = 0; i < EX_NR_MAX; i++)
    {
        if (explodes[i].tick_left <= EX_TICK_UNUSED)
        {
            explodes[i].tick_left = EX_TICK_FULL;
            explodes[i].x = x;
            explodes[i].y = y;
            return;
        }
    }
}

void blit_explode(SDL_Surface *target)
{
    int i;
    for (i = 0; i < EX_NR_MAX; i++)
    {
        Explode *curr_explode = &(explodes[i]);
        if(curr_explode->tick_left > EX_TICK_UNUSED){
            curr_explode->tick_left -= 1;
            int current_frame_nr = rand() % EX_FRAME_NR;
            super_blit(explode_frames[current_frame_nr], target, 
            curr_explode->x, curr_explode->y, 0);
        }
    }
}


