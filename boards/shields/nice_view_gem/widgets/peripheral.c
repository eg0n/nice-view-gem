#include <stdio.h>
#include <zephyr/kernel.h>
#include "peripheral.h"
#include "../assets/custom_fonts.h"

/* The peripheral's row, under the battery: OFF when it isn't linked, else its signal strength
 * (ESB split) or battery level (BLE split). */
void draw_peripheral_status(lv_obj_t *canvas, const struct status_state *state) {
    lv_draw_label_dsc_t label_left_dsc;
    init_label_dsc(&label_left_dsc, LVGL_FOREGROUND, &pixel_operator_mono, LV_TEXT_ALIGN_LEFT);
    canvas_draw_text(canvas, 0, 30, 25, &label_left_dsc, "RHS");

    char text[10] = {};
    if (!state->peripheral_connected) {
        snprintf(text, sizeof(text), "OFF");
    } else if (IS_ENABLED(CONFIG_ZMK_SPLIT_ESB)) {
        if (state->peripheral_rssi == 0) {
            snprintf(text, sizeof(text), "--");
        } else {
            snprintf(text, sizeof(text), "%idB", MAX(state->peripheral_rssi, -99));
        }
    } else if (state->peripheral_battery < 0) {
        snprintf(text, sizeof(text), "--%%");
    } else {
        snprintf(text, sizeof(text), "%i%%", state->peripheral_battery);
    }

    lv_draw_label_dsc_t label_right_dsc;
    init_label_dsc(&label_right_dsc, LVGL_FOREGROUND, &pixel_operator_mono, LV_TEXT_ALIGN_RIGHT);
    canvas_draw_text(canvas, 26, 30, 42, &label_right_dsc, text);
}
