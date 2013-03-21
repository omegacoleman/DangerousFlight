
#ifndef _PLAYER_H_
#define _PLAYER_H_

#include "SDL.h"
#include "gear.h"
#include "sprite.h"

typedef struct
{
    SuperBlitable *model;
    GearObject gear;
    int health;
    int max_health;
    int damage_tick_left;
} Player;

Player *create_player(SuperBlitable *model, int x, int y, int weight, int max_health);
void step_player(Player *player);
void blit_player(Player *player, SDL_Surface *target);

#endif

