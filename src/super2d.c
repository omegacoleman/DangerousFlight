/*
 * 未命名.c
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


#include <stdio.h>
#include <SDL/SDL.h>
#include "sprite.h"
#include "environment.h"

#define VIEWPORT_WIDTH 800
#define VIEWPORT_HEIGHT 600

int process_events(const SDL_Event *event);
int quited = 0;


int main(int argc, char **argv)
{
    SuperBlitable *plane;
    
	SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER);
    atexit(SDL_Quit);
    SDL_SetEventFilter(process_events);
    SDL_Surface *screen = SDL_SetVideoMode(VIEWPORT_WIDTH, VIEWPORT_HEIGHT, 32, 0);
    load_models();
    load_environment("env_sea");
    plane = get_model("ca_r");
    unsigned long frame = 0;
    while (! quited) {
        SDL_PollEvent(NULL);
        blit_bg(screen);
        super_blit(plane, screen, VIEWPORT_WIDTH / 2, VIEWPORT_HEIGHT / 2);
        env_move_on();
        SDL_Flip(screen);
        SDL_Delay(20);
        frame++;
    }
	return 0;
}

int process_events(const SDL_Event *event)
{
    switch (event->type) {
        case SDL_MOUSEBUTTONDOWN:
        case SDL_QUIT:
        quited = 1;
        break;
    }
    return 0;
}

