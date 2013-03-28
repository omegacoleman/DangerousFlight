
#include "global.h"

#include "sprite.h"
#include "bottom.h"
#include "spec.h"
#include "environment.h"
#include "SDL_rotozoom.h"
#include "SDL.h"
#include "SDL_image.h"
#include "alphachannel.h"
#include <string.h>

#define MODEL_NR 4

char model_basenames[MODEL_NR][255] = 
{
    "ca_w", 
    "ca_r", 
    "missle", 
    "envobj_sea", 
};

#define EXT_ORIG ".jpg"
#define EXT_ALPH "_alph.jpg"
#define EXT_SPEC "_spec.jpg"
#define EXT_Z "_z.jpg"

#define DEF_BLUR 20

SuperBlitable models[MODEL_NR];

void load_models()
{
    int i;
    IMG_Init(IMG_INIT_JPG);
    for (i = 0; i < MODEL_NR; i++)
    {
        char filename_orig[255];
        char filename_alph[255];
        char filename_spec[255];
        char filename_z[255];
        strcpy(filename_orig, RES_DIR);
        strcpy(filename_alph, RES_DIR);
        strcpy(filename_spec, RES_DIR);
        strcpy(filename_z, RES_DIR);
        strcat(filename_orig, model_basenames[i]);
        strcat(filename_alph, model_basenames[i]);
        strcat(filename_spec, model_basenames[i]);
        strcat(filename_z, model_basenames[i]);
        strcat(filename_orig, EXT_ORIG);
        strcat(filename_alph, EXT_ALPH);
        strcat(filename_spec, EXT_SPEC);
        strcat(filename_z, EXT_Z);
        models[i].orig = IMG_Load(filename_orig);
        models[i].alph = IMG_Load(filename_alph);
        models[i].spec = IMG_Load(filename_spec);
        models[i].z = IMG_Load(filename_z);
        models[i].curr = SDL_DisplayFormatAlpha(models[i].orig);
        models[i].curr_flag = SB_CF_FIRST;
    }
    IMG_Quit();
}

SuperBlitable* get_model(char *name)
{
    int i;
    for (i = 0; i < MODEL_NR; i++)
    {
        if(strcmp(name, model_basenames[i]) == 0)
        {
            return &(models[i]);
        }
    }
    return NULL;
}

void super_blit(SuperBlitable *superb, SDL_Surface *dest, 
int x, int y, int angle)
{
    SDL_Surface *s_final;
    Uint32 curr_spec = get_spec();
    if ((superb->last_spec != curr_spec) || \
    (superb->curr_flag != SB_CF_NORMAL)) {
        SDL_Surface *s_n_spec;
        Uint8 sr, sg, sb;
        SDL_GetRGB(curr_spec, get_spec_fmt(), &sr, &sg, &sb);
        SDL_FreeSurface(superb->curr);
        superb->curr = SDL_DisplayFormatAlpha(superb->orig);
        s_n_spec = 
        SDL_ConvertSurface(superb->spec, superb->spec->format, 0);
        change_style(s_n_spec, SDL_MapRGB(s_n_spec->format, sr, sg, sb));
        change_spec(superb->curr, s_n_spec);
        set_alpha_channel(superb->curr, superb->alph);
        SDL_FreeSurface(s_n_spec);
        superb->curr_flag = SB_CF_NORMAL;
    }
    s_final = rotozoomSurface(superb->curr, angle, 1, 0);
    center_blit(s_final, dest, x, y);
    SDL_FreeSurface(s_final);
}

void fast_blit(SuperBlitable *superb, SDL_Surface *dest, int x, int y)
{
    if ((superb->curr_flag != SB_CF_FAST)) {
        SDL_FreeSurface(superb->curr);
        superb->curr = SDL_DisplayFormatAlpha(superb->orig);
        set_alpha_channel(superb->curr, superb->alph);
        superb->curr_flag = SB_CF_FAST;
    }
    center_blit(superb->curr, dest, x, y);
}

// Well, in fact, this should be in bottom.c, but I wanna
// do all the bliting in this file, so..
void center_blit(SDL_Surface *tob, SDL_Surface *dest, int x, int y)
{
    SDL_Rect thisrect;
    thisrect.x = x - (tob->w / 2);
    thisrect.y = y - (tob->h / 2);
    thisrect.w = tob->w;
    thisrect.h = tob->h;
    SDL_BlitSurface(tob, NULL, dest, &thisrect);
}

