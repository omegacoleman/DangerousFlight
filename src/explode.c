
#include <stdlib.h>
#include "SDL_image.h"
#include "explode.h"
#include "math.h"
#include "sprite.h"


#define EX_TICK_FULL 10
#define EX_TICK_UNUSED -1
#define EX_NR_MAX 32
#define EX_FRAME_NR 3
#define EX_MODEL_NAME "res/explode_%d.png"
#define EX_R 150
#define EX_TYPE_FIRE 2
#define EX_TYPE_ANIM 1
#define EX_FIREAMOUNT 5

Explode explodes[EX_NR_MAX];
SDL_Surface *explode_frames[EX_FRAME_NR];

void take_explosive(int x, int y, int type);

void explode_init()
{
    int i = 0;
    for (i = 0; i < EX_NR_MAX; i++)
    {
        explodes[i].tick_left = EX_TICK_UNUSED;
    }
    IMG_Init(IMG_INIT_PNG);
    for (i = 0; i < EX_FRAME_NR; i++)
    {
        char mname[255];
        sprintf(mname, EX_MODEL_NAME, i);
        explode_frames[i] = IMG_Load(mname);
    }
    IMG_Quit();
}

void explosive_at(int x, int y)
{
    take_explosive(x, y, EX_TYPE_ANIM);
}

void fire_at(int x, int y)
{
    take_explosive(x, y, EX_TYPE_FIRE);
}

void take_explosive(int x, int y, int type)
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
        int s;
        Explode *curr_explode = &(explodes[i]);
        int amount;
        if(curr_explode->tick_left > EX_TICK_UNUSED){
            curr_explode->tick_left -= 1;
            amount = 1;
            if (curr_explode->type == EX_TYPE_FIRE)
            {
                amount = EX_FIREAMOUNT;
            }
            for (s = 0; s < amount; s++)
            {
                int current_frame_nr = rand() % EX_FRAME_NR;
                center_blit(explode_frames[current_frame_nr], target, 
                curr_explode->x - EX_R / 2 + (rand() % EX_R), 
                curr_explode->y - EX_R / 2 + (rand() % EX_R));
            }
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
            xdiff = explodes[i].x - x;
            ydiff = explodes[i].y - y;
            dis = (int) sqrt(xdiff * xdiff + ydiff * ydiff);
            if(dis < EX_R)
            {
                harm += 120;
            }
        }
    }
    return harm;
}

