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
#include <SDL/SDL_image.h>
#include "alphachannel.h"
#include "spec.h"

#define VIEWPORT_WIDTH 800
#define VIEWPORT_HEIGHT 600

int process_events(const SDL_Event *event);
int quited = 0;


int main(int argc, char **argv)
{
	SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER);
    atexit(SDL_Quit);
    SDL_SetEventFilter(process_events);
    SDL_Surface *screen = SDL_SetVideoMode(VIEWPORT_WIDTH, VIEWPORT_HEIGHT, 32, 0);
    
    
    SDL_Surface *s_bg, *s_normal, *s_alpha, *s_spec, *s_n_spec, *s_z;
    IMG_Init(IMG_INIT_PNG | IMG_INIT_JPG);
    s_bg = SDL_DisplayFormatAlpha(IMG_Load("res/tmp-bg.png"));
    s_normal = SDL_DisplayFormatAlpha(IMG_Load("res/ca_r.jpg"));
    s_alpha = SDL_DisplayFormat(IMG_Load("res/ca_r_alph.jpg"));
    s_spec = SDL_DisplayFormat(IMG_Load("res/ca_r_spec.jpg"));
    s_z = SDL_DisplayFormat(IMG_Load("res/ca_r_z.jpg"));
    IMG_Quit();
    
    s_n_spec = SDL_ConvertSurface(s_spec, s_spec->format, 0);
    change_style(s_n_spec, SDL_MapRGB(s_n_spec->format, 0, 0, 255));
    change_spec(s_normal, s_n_spec);
    int frame = 0;
    while (! quited) {
        SDL_PollEvent(NULL);
        SDL_BlitSurface(s_bg, NULL, screen, NULL);
        set_alpha_channel(s_normal, s_alpha);
        // z_cut(s_normal, s_z, frame, 10);
        SDL_BlitSurface(s_normal, NULL, screen, NULL);
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

