#include "SDL_helper.h"
#include "common.h"

void SDL_ClearScreen(SDL_Renderer *renderer, SDL_Color colour) {
    SDL_SetRenderDrawColor(renderer, colour.r, colour.g, colour.b, colour.a);
    SDL_RenderClear(renderer);
}

void SDL_DrawRect(SDL_Renderer *renderer, int x, int y, int w, int h, SDL_Color colour) {
    SDL_Rect rect;
    rect.x = x;
    rect.y = y;
    rect.w = w;
    rect.h = h;
    SDL_SetRenderDrawColor(RENDERER, colour.r, colour.g, colour.b, colour.a);
    SDL_RenderFillRect(RENDERER, &rect);
}

void SDL_DrawCircle(SDL_Renderer *renderer, int x, int y, int r, SDL_Color colour) {
    filledCircleRGBA(renderer, x, y, r, colour.r, colour.g, colour.b, colour.a);
    return;
}

void SDL_DrawText(SDL_Renderer *renderer, FC_Font *font, int x, int y, SDL_Color colour, const char *str) {
    SDL_Rect position;
    position.x = x;
    position.y = y;
    FC_DrawBoxColor(font, renderer, position, colour, str);
}

void SDL_DrawTextf(SDL_Renderer *renderer, FC_Font *font, int x, int y, SDL_Color colour, const char *text, ...) {
    char buffer[256];
    va_list args;
    va_start(args, text);
    vsnprintf(buffer, 256, text, args);
    SDL_DrawText(renderer, font, x, y, colour, buffer);
    va_end(args);
}

void SDL_LoadImage(SDL_Renderer *renderer, SDL_Texture **texture, char *path) {
    SDL_Surface *loaded_surface = NULL;
    loaded_surface = IMG_Load(path);

    if (loaded_surface) {
        Uint32 colorkey = SDL_MapRGB(loaded_surface->format, 0, 0, 0);
        SDL_SetColorKey(loaded_surface, SDL_TRUE, colorkey);
        *texture = SDL_CreateTextureFromSurface(renderer, loaded_surface);
    }

    SDL_FreeSurface(loaded_surface);
}

void SDL_DrawImage(SDL_Renderer *renderer, SDL_Texture *texture, int x, int y) {
    SDL_Rect position;
    position.x = x;
    position.y = y;
    SDL_QueryTexture(texture, NULL, NULL, &position.w, &position.h);
    SDL_RenderCopy(renderer, texture, NULL, &position);
}

void SDL_DrawImageScale(SDL_Renderer *renderer, SDL_Texture *texture, int x, int y, int w, int h) {
    SDL_Rect position;
    position.x = x;
    position.y = y;
    position.w = w;
    position.h = h;
    SDL_RenderCopy(renderer, texture, NULL, &position);
}
