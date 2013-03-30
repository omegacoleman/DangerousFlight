/*
 * 
 * Copyright 2013 Stephen Coleman <omegacoleman@gmail.com>
 * 
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 * 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston,
 * MA 02110-1301, USA.
 * 
 * 
 */

#include "global.h"



#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "SDL.h"
#include "sprite.h"
#include "player.h"
#include "environment.h"
#include "missle.h"
#include "explode.h"
#include "ui.h"

#define PLAYER_WEIGHT 3
#define PLAYER_HEALTH_MAX 5000
#define VIEWPORT_WIDTH 800
#define VIEWPORT_HEIGHT 600
#define FPS_MAX 40
#define FPS_MAX_DELAY (1000 / FPS_MAX)

#define PLAYER_STARTUP_POS_X 300
#define PLAYER_STARTUP_POS_Y 300

int process_events(const SDL_Event *event);
int quited = 0;
Player *player;

Missle *side_gen_missle();

int main(int argc, char **argv)
{
    SDL_Surface *screen;
    Missle *missle;
    int tick_at_start, tick_gone;
    unsigned long frame = 0;
    int died = 0, close_tick_left;
    
    srand((unsigned)time(NULL));
    putenv ("SDL_VIDEO_WINDOW_POS");
    putenv ("SDL_VIDEO_CENTERED=1");
    SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER);
    atexit(SDL_Quit);
    SDL_SetEventFilter(process_events);
    screen = SDL_SetVideoMode(VIEWPORT_WIDTH, VIEWPORT_HEIGHT, 
    32, SDL_HWSURFACE | SDL_DOUBLEBUF);
    SDL_WM_SetCaption("Dangerous Flight", "DF");
    
    SIGN_RESTART:
    
    load_models();
    ui_init();
    explode_init();
    set_walls(0, VIEWPORT_HEIGHT, 0, VIEWPORT_WIDTH);
    load_environment("sea");
    missle_init();
    
    frame = 0;
    died = 0;
    quited = 0;
    
    player = create_player(get_model("ca_r"), 
    PLAYER_STARTUP_POS_X, PLAYER_STARTUP_POS_Y, 
    PLAYER_WEIGHT, PLAYER_HEALTH_MAX);
    
    missle = side_gen_missle();
    
    while (! quited) {
        tick_at_start = SDL_GetTicks();
        SDL_PollEvent(NULL);
        blit_bg(screen);
        blit_missle(missle, screen);
        blit_player(player, screen);
        blit_explode(screen);
        draw_lifebar(screen, player->health, 0, 0);
        kb_control(player, SDL_GetKeyState(NULL));
        step_player(player);
        if (step_missle(missle) != 1)
        {
            missle = side_gen_missle();
        }
        env_move_on();
        SDL_Flip(screen);
        tick_gone = SDL_GetTicks() - tick_at_start;
        if (FPS_MAX_DELAY > tick_gone)
        {
            SDL_Delay(FPS_MAX_DELAY - tick_gone);
        }
        if ((! died) && (player->health <= 0))
        {
            close_tick_left = 100;
            died = 1;
        }
        if ((died) && (close_tick_left > 0))
        {
            close_tick_left -= 1;
        }
        if ((died) && (close_tick_left <= 0))
        {
            died = -1;
            quited = 1;
        }
        if (frame == 0)
        {
            intro(screen);
        }
        frame++;
    }
    if (died == -1)
    {
        quited = 0;
        gameover(screen);
        if (!quited)
        {
            goto SIGN_RESTART;
        }
    }
    return 0;
}

Missle *side_gen_missle()
{
    Missle *missle;
    if (rand() % 2)
    {
        missle = gen_missle(VIEWPORT_WIDTH, rand() % VIEWPORT_HEIGHT);
    } else {
        missle = gen_missle(0, rand() % VIEWPORT_HEIGHT);
    }
    lock_gear(missle, &(player->gear));
    return missle;
}

int process_events(const SDL_Event *event)
{
    switch (event->type) {
        // case SDL_MOUSEBUTTONDOWN:
        case SDL_KEYDOWN:
        if (locked && (event->key.keysym.sym == key_lookin_for))
        {
            locked = 0;
        }
        break;
        case SDL_QUIT:
        quited = 1;
        if (locked)
        {
            locked = 0;
        }
        break;
    }
    return 0;
}

