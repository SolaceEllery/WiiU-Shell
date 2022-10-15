#pragma once

#include <stdbool.h>

int FS_MakeDir(const char *path);
int FS_RecursiveMakeDir(const char *dir);
bool FS_FileExists(const char *path);
bool FS_DirExists(const char *path);
const char *FS_GetFileExt(const char *filename);
char *FS_GetFileModifiedTime(const char *filename);
uint32_t FS_GetFileSize(const char *filename);