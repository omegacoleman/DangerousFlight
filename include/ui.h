
#ifndef _UI_H_
#define _UI_H_

#include "SDL.h"

void intro(SDL_Surface *screen);
void ui_init();
void draw_lifebar(SDL_Surface *dest, int life, int x, int y);
void gameover(SDL_Surface *screen);

extern int locked;
extern SDLKey key_lookin_for;

#endif


