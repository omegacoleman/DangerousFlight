
#include "global.h"

#include "SDL.h"
#include "SDL_image.h"
#include "ui.h"
#include "sprite.h"

#define S_FN_LIFECROSS "res/lifec.png"
#define S_FN_INTRO "res/intro.png"
#define S_FN_GAMEOVER "res/gameover.png"

SDL_Surface *s_lifecross;
SDL_Surface *s_intro, *s_gameover;
SDLKey key_lookin_for;

int locked;

void display_locked(SDL_Surface *screen, SDL_Surface *lock, Uint32 key);

void ui_init()
{
    locked = 0;
    IMG_Init(IMG_INIT_PNG);
    s_lifecross = IMG_Load(S_FN_LIFECROSS);
    s_intro = IMG_Load(S_FN_INTRO);
    s_gameover = IMG_Load(S_FN_GAMEOVER);
    IMG_Quit();
}

void draw_lifebar(SDL_Surface *dest, int life, int x, int y)
{
    int cross_nr = life / 450;
    SDL_Rect thisrect;
    int i;
    if(life == 0)
    {
        return;
    }
    cross_nr += 1;
    thisrect.x = x;
    thisrect.y = y;
    thisrect.w = s_lifecross->w;
    thisrect.h = s_lifecross->h;
    for (i = 0; i < cross_nr; i++)
    {
        SDL_BlitSurface(s_lifecross, NULL, dest, &thisrect);
        thisrect.x += s_lifecross->w;
    }
}

void intro(SDL_Surface *screen)
{
    display_locked(screen, s_intro, SDLK_UP);
}

void gameover(SDL_Surface *screen)
{
    display_locked(screen, s_gameover, SDLK_SPACE);
}

void display_locked(SDL_Surface *screen, SDL_Surface *lock, SDLKey key)
{
    SDL_Surface *dest;
    key_lookin_for = key;
    locked = 1;
    dest = SDL_DisplayFormat(screen);
    center_blit(lock, screen, screen->w / 2, screen->h / 2);
    SDL_Flip(screen);
    while (locked)
    {
        SDL_PollEvent(NULL);
        SDL_Delay(100);
    }
    center_blit(dest, screen, screen->w / 2, screen->h / 2);
    SDL_Flip(screen);
}


