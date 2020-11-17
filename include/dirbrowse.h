#ifndef WIIU_SHELL_DIRBROWSE_H
#define WIIU_SHELL_DIRBROWSE_H

#include <stdbool.h>

typedef struct File
{
	struct File *next; // Next item
	int isDir;          // Folder flag
	int isReadOnly;     // Read-only flag
	int isHidden;       // Hidden file flag
	char name[256];       // File name
	char ext[4];        // File extension
	uint32_t size;           // File size
} File;

extern File *files;

extern int initialPosition;
extern int position;
extern int fileCount;

extern int multi_select_index;
extern bool multi_select[256];
extern int multi_select_indices[256];
extern char multi_select_dir[512];
extern char multi_select_paths[256][512];

void Dirbrowse_RecursiveFree(File *node);
void Dirbrowse_PopulateFiles(bool clear);
void Dirbrowse_DisplayFiles(void);
File *Dirbrowse_GetFileIndex(int index);
void Dirbrowse_OpenFile(void);
int Dirbrowse_Navigate(bool parent);

#endif