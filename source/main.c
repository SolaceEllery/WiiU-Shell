#include <proc_ui/procui.h>
#include <romfs-wiiu.h>
#include <stdio.h>
#include <whb/proc.h>

#include "common.h"
#include "config.h"
#include "fs.h"
#include "menu_main.h"
#include "state.h"
#include "textures.h"
#include "utils.h"

#include <coreinit/memory.h>

#define SCREEN_COLOR_BLACK ((SDL_Color){.r = 0x00, .g = 0x00, .b = 0x00, .a = 0xFF})

#ifdef DEBUG

#include <sys/iosupport.h>
#include <unistd.h>
#include <whb/log.h>
#include <whb/log_udp.h>

static devoptab_t dotab_stdout;
static ssize_t wiiu_log_write(struct _reent *r, void *fd, const char *ptr, size_t len) {
    WHBLogPrintf("%*.*s", len, len, ptr);
    return len;
}

#endif


static void Term_Services(void) {
    Textures_Free();

    FC_FreeFont(Roboto_OSK);
    FC_FreeFont(Roboto_small);
    FC_FreeFont(Roboto);
    FC_FreeFont(Roboto_large);
    TTF_Quit();

    Mix_CloseAudio();
    Mix_Quit();

    IMG_Quit();
    /*
	SDL_DestroyRenderer(RENDERER);
	SDL_FreeSurface(WINDOW_SURFACE);
	SDL_DestroyWindow(WINDOW);*/

#ifdef DEBUG
    WHBLogUdpDeinit();
#endif

    SDL_Quit();
    romfsExit();
}

static void Init_Services(void) {
    initState();
    romfsInit();
    SDL_Init(SDL_INIT_EVERYTHING);

#ifdef DEBUG
    WHBLogUdpInit();
    memset(&dotab_stdout, 0, sizeof(devoptab_t));
    dotab_stdout.name = "stdout_udp";
    dotab_stdout.write_r = &wiiu_log_write;
    devoptab_list[STD_OUT] = &dotab_stdout;
    devoptab_list[STD_ERR] = &dotab_stdout;
#endif

    WINDOW = SDL_CreateWindow(NULL, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 0, 0, SDL_WINDOW_FULLSCREEN_DESKTOP);
    RENDERER = SDL_CreateRenderer(WINDOW, -1, SDL_RENDERER_ACCELERATED);

    WINDOW_SURFACE = SDL_GetWindowSurface(WINDOW);

    SDL_SetRenderDrawBlendMode(RENDERER, SDL_BLENDMODE_BLEND);

    SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "2");

    IMG_Init(IMG_INIT_PNG | IMG_INIT_JPG);

    Mix_Init(MIX_INIT_FLAC | MIX_INIT_MOD | MIX_INIT_MP3 | MIX_INIT_OGG | MIX_INIT_MID);
    Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, MIX_DEFAULT_CHANNELS, 4096);

    void *fontData = NULL;
    uint32_t fontSize = 0;
    OSGetSharedData(OS_SHAREDDATATYPE_FONT_STANDARD, 0, &fontData, &fontSize);

    TTF_Init();
    Roboto_large = FC_CreateFont();
    Roboto = FC_CreateFont();
    Roboto_small = FC_CreateFont();
    Roboto_OSK = FC_CreateFont();
    FC_LoadFont_RW(Roboto_large, RENDERER, SDL_RWFromMem(fontData, fontSize), 1, 30, SCREEN_COLOR_BLACK, TTF_STYLE_NORMAL);
    FC_LoadFont_RW(Roboto, RENDERER, SDL_RWFromMem(fontData, fontSize), 1, 25, SCREEN_COLOR_BLACK, TTF_STYLE_NORMAL);
    FC_LoadFont_RW(Roboto_small, RENDERER, SDL_RWFromMem(fontData, fontSize), 1, 20, SCREEN_COLOR_BLACK, TTF_STYLE_NORMAL);
    FC_LoadFont_RW(Roboto_OSK, RENDERER, SDL_RWFromMem(fontData, fontSize), 1, 50, SCREEN_COLOR_BLACK, TTF_STYLE_NORMAL);
    if (!Roboto_large || !Roboto || !Roboto_small || !Roboto_OSK)
        Term_Services();

    Textures_Load();

    FS_RecursiveMakeDir("wiiu/WiiU-Shell/");

    if (FS_FileExists("wiiu/WiiU-Shell/lastdir.txt")) {
        char *buf = (char *) malloc(256);

        FILE *read = fopen("wiiu/WiiU-Shell/lastdir.txt", "r");
        fscanf(read, "%s", buf);
        fclose(read);

        if (FS_DirExists(buf)) // Incase a directory previously visited had been deleted, set start path to sdmc:/ to avoid errors.
            strcpy(cwd, buf);
        else
            strcpy(cwd, START_PATH);

        free(buf);
    } else {
        char *buf = (char *) malloc(256);
        strcpy(buf, START_PATH);

        FILE *write = fopen("wiiu/WiiU-Shell/lastdir.txt", "w");
        fprintf(write, "%s", buf);
        fclose(write);

        strcpy(cwd, buf); // Set Start Path to "sdmc:/" if lastDir.txt hasn't been created.

        free(buf);
    }

    Config_Load();
}

int main(int argc, char **argv) {
    Init_Services();
    debugInit();

    if (setjmp(exitJmp)) {
        Term_Services();
        if (!isAroma())
            WHBProcShutdown();
        ProcUIShutdown();
        return 0;
    }

    MENU_DEFAULT_STATE = MENU_STATE_HOME;
    Menu_Main();
    Term_Services();
}
