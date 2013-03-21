
#include "missle.h"
#include "explode.h"
#include "math.h"


#define EXPLODE_TICK_MAX 30
#define EXPLODE_TICK_MIN 20
#define EXPLODE_TICK_GAP (EXPLODE_TICK_MAX - EXPLODE_TICK_MIN)

#define MISSLE_PUSH_X_MAX -30
#define MISSLE_PUSH_X_MIN -70
#define MISSLE_PUSH_Y_MAX 7
#define MISSLE_PUSH_Y_MIN -7
#define MISSLE_WEIGHT 2

#define MISSLE_ACTIVE_R 50

#define MISSLE_PUSH_X_GAP (MISSLE_PUSH_X_MAX - MISSLE_PUSH_X_MIN)
#define MISSLE_PUSH_Y_GAP (MISSLE_PUSH_Y_MAX - MISSLE_PUSH_Y_MIN)

SuperBlitable *missle_model;

void missle_init()
{
    missle_model = get_model("missle");
}

void lock_gear(Missle *missle, GearObject * gear)
{
    missle->target.gear = gear;
    missle->target.type = MT_GEAROBJ;
}

void lock_point(Missle *missle, int x, int y)
{
    missle->target.x = x;
    missle->target.y = y;
    missle->target.type = MT_STATIC;
}

Missle *gen_missle(int x, int y)
{
    Missle *curr = malloc(sizeof(Missle));
    curr->target.type = MT_NONE;
    curr->explode_tick_left = \
    EXPLODE_TICK_MIN + (rand() % EXPLODE_TICK_GAP);
    init_gear(&(curr->gear), x, y, MISSLE_WEIGHT);
    int x_push = MISSLE_PUSH_X_MIN + (rand() % MISSLE_PUSH_X_GAP);
    int y_push = MISSLE_PUSH_Y_MIN + (rand() % MISSLE_PUSH_Y_GAP);
    give_push(&(curr->gear), x_push, y_push);
}

int step_missle(Missle *missle)
{
    missle->explode_tick_left -= 1;
    int explode = 0;
    if (missle->target.type != MT_NONE)
    {
        int target_x, target_y;
        if (missle->target.type == MT_STATIC)
        {
            target_x = missle->target.x;
            target_y = missle->target.y;
        }
        if (missle->target.type == MT_GEAROBJ)
        {
            target_x = missle->target.gear->x;
            target_y = missle->target.gear->y;
        }
        int x_offs = target_x - missle->gear.x;
        int y_offs = target_y - missle->gear.y;
        int distance = sqrt(x_offs * x_offs + y_offs * y_offs);
        if (distance < MISSLE_ACTIVE_R)
        {
            explode = 1;
        }
    }
    if (missle->explode_tick_left <= 0)
    {
        explode = 1;
    }
    if (explode)
    {
        fire_at(missle->gear.x, missle->gear.y);
        free(missle);
        return 0;
    }
    step_gear(&(missle->gear));
    return 1;
}

void blit_missle(Missle *missle, SDL_Surface *dest)
{
    super_blit(missle_model, dest, missle->gear.x, missle->gear.y, missle->gear.angle);
}

