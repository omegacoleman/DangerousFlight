
#include <stdlib.h>
#include "explode.h"
#include "math.h"
#include "sprite.h"


#define ABS(a) ((a>0?a:-a))

#define EX_TICK_FULL 10
#define EX_TICK_UNUSED -1
#define EX_NR_MAX 32
#define EX_FRAME_NR 10
#define EX_MODEL_NAME "explode_%d"
#define EX_R 250
#define EX_TYPE_FIRE 2
#define EX_TYPE_ANIM 1

Explode explodes[EX_NR_MAX];
SuperBlitable *explode_frames[EX_FRAME_NR];

int take_explosive(int x, int y, int type);

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
    take_explosive(x, y, EX_TYPE_ANIM);
}

int fire_at(int x, int y)
{
    take_explosive(x, y, EX_TYPE_FIRE);
}

int take_explosive(int x, int y, int type)
{
    int i = 0;
    for (i = 0; i < EX_NR_MAX; i++)
    {
        if (explodes[i].tick_left <= EX_TICK_UNUSED)
        {
            explodes[i].tick_left = EX_TICK_FULL;
            explodes[i].x = x;
            explodes[i].y = y;
            explodes[i].type = type;
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
            fast_blit(explode_frames[current_frame_nr], target, 
            curr_explode->x, curr_explode->y);
        }
    }
}

int hit_test(int x, int y)
{
    int i, harm = 0;
    for (i = 0; i < EX_NR_MAX; i++)
    {
        if ((explodes[i].tick_left > EX_TICK_UNUSED) && (explodes[i].type == EX_TYPE_FIRE))
        {
            int xdiff, ydiff, dis;
            xdiff = ABS(explodes[i].x - x);
            ydiff = ABS(explodes[i].y - y);
            dis = sqrt(xdiff * xdiff + ydiff * ydiff);
            if(dis < EX_R)
            {
                harm += (EX_R - dis);
            }
        }
    }
    return harm;
}

