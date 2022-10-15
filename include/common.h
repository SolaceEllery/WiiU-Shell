#ifndef WIIU_SHELL_COMMON_H
#define WIIU_SHELL_COMMON_H

#include <setjmp.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL2_gfxPrimitives.h> 
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL_ttf.h>
#include "SDL_FontCache.h"

#define wait(msec) SDL_Delay(msec)

extern jmp_buf exitJmp;

extern SDL_Window *WINDOW;
extern SDL_Surface *WINDOW_SURFACE;
extern SDL_Renderer *RENDERER;
extern FC_Font *Roboto_large, *Roboto, *Roboto_small, *Roboto_OSK;

#define ROOT_PATH "/vol/external01/"
#define START_PATH ROOT_PATH
#define MAX_FILES 2048
#define FILES_PER_PAGE 8

extern int MENU_DEFAULT_STATE;
extern int BROWSE_STATE;

enum MENU_STATES
{
    MENU_STATE_HOME = 0,
    MENU_STATE_OPTIONS = 1,
    MENU_STATE_MENUBAR = 2,
    MENU_STATE_SETTINGS = 3,
    MENU_STATE_FTP = 4,
    MENU_STATE_SORT = 5,
    MENU_STATE_DELETE_DIALOG = 6,
    MENU_STATE_PROPERTIES = 7
};

enum BROWSE_STATES
{
    STATE_SD = 0,
    STATE_NAND = 1
};

extern char cwd[512];

#endif
