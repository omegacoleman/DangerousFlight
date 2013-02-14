
#include <stdlib.h>
#include "environment.h"
#include "bottom.h"
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>

#define EXT_BG ".jpg"
#define EXT_OPT "_ops.bmp"

Environment curr_environment;
int curr_spec_pix;
int curr_fog_pix;

void load_environment(char *name)
{
    IMG_Init(IMG_INIT_JPG);
    char fullname_bg[255] = RES_DIR;
    char fullname_opt[255] = RES_DIR;
    strcat(fullname_bg, name);
    strcat(fullname_opt, name);
    strcat(fullname_bg, EXT_BG);
    strcat(fullname_opt, EXT_OPT);
    curr_environment.bg = SDL_DisplayFormat(IMG_Load(fullname_bg));
    curr_environment.optlines = IMG_Load(fullname_opt);
    IMG_Quit();
    curr_spec_pix = 0;
    curr_fog_pix = 0;
}

void blit_bg(SDL_Surface *dest)
{
    SDL_BlitSurface(curr_environment.bg, NULL, dest, NULL);
}

void env_move_on()
{
    curr_spec_pix += rand() % 5;
    curr_fog_pix += 1;
    curr_spec_pix %= curr_environment.optlines->w * 2;
    curr_fog_pix %= curr_environment.optlines->w * 2;
}

Uint32 get_spec()
{
    int real_spec_x;
    if(curr_spec_pix < curr_environment.optlines->w)
    {
        real_spec_x = curr_spec_pix;
    } else {
        real_spec_x = 
        (2 * curr_environment.optlines->w) - curr_spec_pix - 1;
    }
    return get_pixel(curr_environment.optlines, 
    real_spec_x, OPT_SPEC_LN);
}

Uint8 get_fog()
{
    int real_fog_x;
    if(curr_fog_pix < curr_environment.optlines->w)
    {
        real_fog_x = curr_fog_pix;
    } else {
        real_fog_x = 
        (2 * curr_environment.optlines->w) - curr_fog_pix - 1;
    }
    Uint32 fog_pix;
    fog_pix = get_pixel(curr_environment.optlines, 
    real_fog_x, OPT_FOG_LN);
    Uint8 fog, garbage;
    SDL_GetRGB(fog_pix, curr_environment.optlines->format, 
    &fog, &garbage, &garbage);
    return fog;
}

SDL_PixelFormat *get_spec_fmt()
{
    return curr_environment.optlines->format;
}


