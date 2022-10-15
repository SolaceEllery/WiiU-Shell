#include "common.h"

jmp_buf exitJmp;

SDL_Window *WINDOW;
SDL_Surface *WINDOW_SURFACE;
SDL_Renderer *RENDERER = NULL;
FC_Font *Roboto_large = NULL;
FC_Font *Roboto = NULL;
FC_Font *Roboto_small = NULL;
FC_Font *Roboto_OSK = NULL;

int MENU_DEFAULT_STATE;
int BROWSE_STATE;

char cwd[512];
