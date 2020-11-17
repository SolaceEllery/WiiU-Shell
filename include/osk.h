#ifndef WIIU_SHELL_OSK_H
#define WIIU_SHELL_OSK_H

#define MAX_Y 4
#define MAX_X 9

extern char osk_buffer[256];

void OSK_Display(char *title, char *msg);

#endif
