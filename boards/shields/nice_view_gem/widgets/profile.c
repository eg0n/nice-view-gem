#include <zephyr/kernel.h>
#include <zmk/ble.h>
#include "profile.h"

/* One dot per profile the keyboard has: the corners of a 3x3 square, 7 px apart. */
static void draw_inactive_profiles(lv_obj_t *canvas, const struct status_state *state) {
    lv_draw_rect_dsc_t rect_white_dsc;
    init_rect_dsc(&rect_white_dsc, LVGL_FOREGROUND);

    for (int i = 0; i < ZMK_BLE_PROFILE_COUNT; i++) {
        for (int corner = 0; corner < 4; corner++) {
            canvas_draw_rect(canvas, 18 + i * 7 + (corner & 1) * 2,
                             129 + BUFFER_OFFSET_BOTTOM + (corner >> 1) * 2, 1, 1, &rect_white_dsc);
        }
    }
}

static void draw_active_profile(lv_obj_t *canvas, const struct status_state *state) {
    lv_draw_rect_dsc_t rect_white_dsc;
    init_rect_dsc(&rect_white_dsc, LVGL_FOREGROUND);

    int offset = state->active_profile_index * 7;

    canvas_draw_rect(canvas, 18 + offset, 129 + BUFFER_OFFSET_BOTTOM, 3, 3, &rect_white_dsc);
}

void draw_profile_status(lv_obj_t *canvas, const struct status_state *state) {
    draw_inactive_profiles(canvas, state);
    draw_active_profile(canvas, state);
}