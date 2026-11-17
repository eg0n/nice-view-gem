#include <stdio.h>
#include <zephyr/kernel.h>
#include "link_stats.h"
#include "../assets/custom_fonts.h"

static void draw_row(lv_obj_t *canvas, int32_t y, const char *label, const char *value) {
    lv_draw_label_dsc_t label_left_dsc;
    init_label_dsc(&label_left_dsc, LVGL_FOREGROUND, &pixel_operator_mono, LV_TEXT_ALIGN_LEFT);
    canvas_draw_text(canvas, 0, y, 25, &label_left_dsc, label);

    lv_draw_label_dsc_t label_right_dsc;
    init_label_dsc(&label_right_dsc, LVGL_FOREGROUND, &pixel_operator_mono, LV_TEXT_ALIGN_RIGHT);
    canvas_draw_text(canvas, 26, y, 42, &label_right_dsc, value);
}

/* A row under the battery: key latency to the central's ACK. */
void draw_link_stats(lv_obj_t *canvas, const struct status_state *state) {
    char text[8];
    uint32_t us = state->key_latency_us;

    if (us == 0) {
        snprintf(text, sizeof(text), "--");
    } else if (us < 10000) {
        snprintf(text, sizeof(text), "%u.%ums", us / 1000, us % 1000 / 100);
    } else if (us < 1000000) {
        snprintf(text, sizeof(text), "%ums", us / 1000);
    } else {
        snprintf(text, sizeof(text), ">1s");
    }
    draw_row(canvas, 30, "LAT", text);
}
