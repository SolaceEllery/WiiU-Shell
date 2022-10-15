#include "input_helper.h"
#include <stdlib.h>
#include <vpad/input.h>

#define TOUCH_PRECISION 10

static uint32_t kHeld = 0, kDown = 0, kUp = 0;
static uint32_t tHeld = 0, tPosX = 0, tPosY = 0;
static uint8_t battStatus = 0;

void Input_Update() {
    VPADStatus vpad;
    VPADReadError vpad_e;

    VPADRead(VPAD_CHAN_0, &vpad, 1, &vpad_e);
    if (vpad_e == VPAD_READ_SUCCESS) {
        kHeld = vpad.hold;
        kDown = vpad.trigger;
        kUp = vpad.release;
        battStatus = vpad.battery;

        VPADTouchData tpdata;
        VPADGetTPCalibratedPoint(VPAD_CHAN_0, &tpdata, &vpad.tpNormal);

        if (tpdata.touched) {
            tHeld = 1;
            if (!(tpdata.validity & VPAD_INVALID_X) && (abs(tPosX - tpdata.x) > TOUCH_PRECISION))
                tPosX = tpdata.x;
            if (!(tpdata.validity & VPAD_INVALID_Y) && (abs(tPosY - tpdata.y) > TOUCH_PRECISION))
                tPosY = tpdata.y;
        } else {
            tHeld = 0;
        }
    }
}

uint8_t Input_BatteryStatus() {
    return battStatus;
}

uint32_t Input_KeysHeld() {
    return kHeld;
}

uint32_t Input_KeysDown() {
    return kDown;
}

uint32_t Input_KeysUp() {
    return kUp;
}

uint32_t Input_TouchCount() {
    return tHeld;
}

void Input_TouchPos(TouchPosition *pos, uint32_t touch) {
    if (touch == 0 && tHeld) {
        pos->px = tPosX;
        pos->py = tPosY;
    } else {
        pos->px = 0;
        pos->py = 0;
    }
}
