#include <stdarg.h>
#include <stdio.h>
#include <string.h>
#include <coreinit/time.h>
#include <whb/log.h>
#include <whb/log_udp.h>

#include "utils.h"

char *Utils_Basename(const char *filename)
{
	char *p = strrchr (filename, '/');
	return p ? p + 1 : (char *) filename;
}

void Utils_GetSizeString(char *string, uint32_t size)
{
	double double_size = (double)size;

	int i = 0;
	static char *units[] = {"B", "KB", "MB", "GB", "TB", "PB", "EB", "ZB", "YB"};

	while (double_size >= 1024.0f)
	{
		double_size /= 1024.0f;
		i++;
	}

	sprintf(string, "%.*f %s", (i == 0) ? 0 : 2, double_size, units[i]);
}

void Utils_SetMax(int *set, int value, int max)
{
	if (*set > max)
		*set = value;
}

void Utils_SetMin(int *set, int value, int min)
{
	if (*set < min)
		*set = value;
}

void Utils_AppendArr(char subject[], const char insert[], int pos)
{
	char buf[100] = {}; // 100 so that it's big enough. fill with 0
	// or you could use malloc() to allocate sufficient space
	
	strncpy(buf, subject, pos); // copy at most first pos characters
	int len = strlen(buf);
	strcpy(buf+len, insert); // copy all of insert[] at the end
	len += strlen(insert);  // increase the length by length of insert[]
	strcpy(buf+len, subject+pos); // copy the rest
	
	strcpy(subject, buf);   // copy it back to subject
	// deallocate buf[] here, if used malloc()
}

static const char days[7][4] = {
    "Sun",
    "Mon",
    "Tue",
    "Wed",
    "Thu",
    "Fri",
    "Sat",
};

static const char months[12][4] = {
    "Jan",
    "Feb",
    "Mar",
    "Apr",
    "May",
    "Jun",
    "Jul",
    "Aug",
    "Sep",
    "Nov",
    "Dec",
};

void debugInit()
{
    WHBLogUdpInit();
}

void debugPrintf(const char *str, ...)
{
    static char newStr[512];

    OSCalendarTime now;
    OSTicksToCalendarTime(OSGetTime(), &now);
    sprintf(newStr, "%s %02d %s %d %02d:%02d:%02d.%03d\t", days[now.tm_wday], now.tm_mday, months[now.tm_mon], now.tm_year, now.tm_hour, now.tm_min, now.tm_sec, now.tm_msec);
    size_t tss = strlen(newStr);

    va_list va;
    va_start(va, str);
    vsnprintf(newStr + tss, 511 - tss, str, va);
    va_end(va);

    WHBLogPrint(newStr);
}