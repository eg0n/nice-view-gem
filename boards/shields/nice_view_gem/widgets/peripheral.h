#pragma once

#include <lvgl.h>
#include "util.h"

struct peripheral_status_state {
    bool connected;
    int8_t battery; /* -1: not reported yet */
};

void draw_peripheral_status(lv_obj_t *canvas, const struct status_state *state);
