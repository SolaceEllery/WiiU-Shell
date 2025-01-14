#pragma once

#include "input_helper.h"
#include <time.h>

#define tapped_inside(touchInfo, x1, y1, x2, y2)  (touchInfo.firstTouch.px >= x1 && touchInfo.firstTouch.px <= x2 && touchInfo.firstTouch.py >= y1 && touchInfo.firstTouch.py <= y2)
#define tapped_outside(touchInfo, x1, y1, x2, y2) (touchInfo.firstTouch.px < x1 || touchInfo.firstTouch.px > x2 || touchInfo.firstTouch.py < y1 || touchInfo.firstTouch.py > y2)

typedef enum TouchState {
    TouchNone,
    TouchStart,
    TouchMoving,
    TouchEnded
} TouchState;

typedef enum TapType {
    TapNone,
    TapShort,
    TapLong
} TapType;

typedef struct TouchInfo {
    TouchState state;
    TouchPosition firstTouch;
    TouchPosition prevTouch;
    TapType tapType;
    time_t touchStart;
} TouchInfo;

void Touch_Init(TouchInfo *touchInfo);
void Touch_Process(TouchInfo *touchInfo);