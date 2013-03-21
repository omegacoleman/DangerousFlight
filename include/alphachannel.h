
#ifndef _ALPHA_CHANNEL_H_
#define _ALPHA_CHANNEL_H_

#include "SDL.h"

void z_cut(SDL_Surface *src, SDL_Surface *s_z, Uint8 tocut, Uint8 blur);
void set_alpha_channel(SDL_Surface *src, SDL_Surface *s_alpha);

#endif


