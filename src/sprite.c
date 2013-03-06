
#include "sprite.h"
#include "bottom.h"
#include "environment.h"
#include "SDL_rotozoom.h"
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <string.h>

#define MODEL_NR 13

char model_basenames[MODEL_NR][255] = 
{
    "ca_w", 
    "ca_r", 
    "missle", 
    "explode_1", 
    "explode_2", 
    "explode_3", 
    "explode_4", 
    "explode_5", 
    "explode_6", 
    "explode_7", 
    "explode_8", 
    "explode_9", 
    "explode_10", 
};

#define EXT_ORIG ".jpg"
#define EXT_ALPH "_alph.jpg"
#define EXT_SPEC "_spec.jpg"
#define EXT_Z "_z.jpg"

#define DEF_BLUR 20

SuperBlitable models[MODEL_NR];

void load_models()
{
    IMG_Init(IMG_INIT_JPG);
    int i;
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
}

void super_blit(SuperBlitable *superb, SDL_Surface *dest, 
int x, int y, int angle)
{
    Uint32 curr_spec = get_spec();
    Uint8 sr, sg, sb;
    SDL_GetRGB(curr_spec, get_spec_fmt(), &sr, &sg, &sb);
    SDL_FreeSurface(superb->curr);
    superb->curr = SDL_DisplayFormatAlpha(superb->orig);
    SDL_Surface *s_n_spec = 
    SDL_ConvertSurface(superb->spec, superb->spec->format, 0);
    change_style(s_n_spec, SDL_MapRGB(s_n_spec->format, sr, sg, sb));
    change_spec(superb->curr, s_n_spec);
    set_alpha_channel(superb->curr, superb->alph);
    if(get_fog() < 0xff)
    {
        z_cut(superb->curr, superb->z, get_fog(), DEF_BLUR);
    }
    superb->curr = rotozoomSurface(superb->curr, angle, 1, 0);
    SDL_Rect thisrect;
    thisrect.x = x - (superb->curr->w / 2);
    thisrect.y = y - (superb->curr->h / 2);
    thisrect.w = superb->curr->w;
    thisrect.h = superb->curr->h;
    SDL_BlitSurface(superb->curr, NULL, dest, &thisrect);
    SDL_FreeSurface(s_n_spec);
}

void fast_blit(SuperBlitable *superb, SDL_Surface *dest, int x, int y)
{
    SDL_FreeSurface(superb->curr);
    superb->curr = SDL_DisplayFormatAlpha(superb->orig);
    set_alpha_channel(superb->curr, superb->alph);
    SDL_Rect thisrect;
    thisrect.x = x - (superb->curr->w / 2);
    thisrect.y = y - (superb->curr->h / 2);
    thisrect.w = superb->curr->w;
    thisrect.h = superb->curr->h;
    SDL_BlitSurface(superb->curr, NULL, dest, &thisrect);
}

