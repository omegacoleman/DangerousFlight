
#include "global.h"


#include "gear.h"
#include "sprite.h"
#include "player.h"
#include "explode.h"
#include "SDL.h"

#define GO_LEFT -4
#define GO_RIGHT 4
#define GO_UP -5

#define PARRY_TIME 5

Player *create_player(SuperBlitable *model, int x, int y,
 int weight, int max_health)
{
    Player *player = malloc(sizeof(Player));
    player->model = model;
    init_gear(&(player->gear), x, y, weight);
    player->health = player->max_health = max_health;
    player->damage_tick_left = 0;
    return player;
}

void step_player(Player *player)
{
    if (player->damage_tick_left > 0)
    {
        player->damage_tick_left -= 1;
        if(rand() > 0.89)
        {
            explosive_at(player->gear.x, player->gear.y);
        }
    }
    if (player->health > 0)
    {
        if (player->damage_tick_left == 0)
        {
            int exploded = hit_test(player->gear.x, player->gear.y);
            player->health -= exploded;
            if (exploded)
            {
                player->damage_tick_left = PARRY_TIME;
            }
        }
        step_gear(&(player->gear));
    }
    if (player->health > player->max_health)
    {
        player->health = player->max_health;
    }
    if (player->health < 0)
    {
        player->health = 0;
    }
}

void blit_player(Player *player, SDL_Surface *target)
{
    if (player->health > 0)
    {
        super_blit(player->model, target, 
        player->gear.x, player->gear.y, player->gear.angle);
    }
}

void kb_control(Player *player, Uint8 *keys)
{
    if (keys[SDLK_UP] == SDL_PRESSED)
    {
        give_push(&(player->gear), 0, GO_UP);
    }
    if (keys[SDLK_LEFT] == SDL_PRESSED)
    {
        give_push(&(player->gear), GO_LEFT, 0);
    }
    if (keys[SDLK_RIGHT] == SDL_PRESSED)
    {
        give_push(&(player->gear), GO_RIGHT, 0);
    }
}


