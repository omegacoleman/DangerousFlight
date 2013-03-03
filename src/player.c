
#include "gear.h"
#include "sprite.h"
#include "player.h"
#include <SDL/SDL.h>

#define GO_LEFT -3
#define GO_RIGHT 3
#define GO_UP -5

Player *create_player(SuperBlitable *model, int x, int y, int weight, int max_health)
{
    Player *player = malloc(sizeof(Player));
    player->model = model;
    init_gear(&(player->gear), x, y, weight);
    player->health = player->max_health = max_health;
    return player;
}

void step_player(Player *player)
{
    step_gear(&(player->gear));
    if (player->health > player->max_health)
    {
        player->health = player->max_health;
    }
}

void blit_player(Player *player, SDL_Surface *target)
{
    super_blit(player->model, target, 
    player->gear.x, player->gear.y, player->gear.angle);
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


