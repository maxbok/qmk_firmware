#include "maxbok.h"

bool rgb_matrix_indicators_advanced_user(uint8_t led_min, uint8_t led_max) {
    switch (get_highest_layer(layer_state)) {
        case _QWERTY:
            rgb_matrix_set_color_all(RGB_OFF);
            break;
        case _SYMBOLS:
            for (int i = 0; i < RGB_MATRIX_LED_COUNT; i++) {
                HSV hsv = { i * 255 / RGB_MATRIX_LED_COUNT, 255, 150 };
                RGB rgb = hsv_to_rgb(hsv);
                rgb_matrix_set_color(i, rgb.r, rgb.g, rgb.b);
            }
            break;
        case _NAV:
            rgb_matrix_set_color_all(RGB_TEAL);
            
            break;
        case _UTILS:
            for (int i = 6; i < 27; i++) {
                rgb_matrix_set_color(i, 10, 10, 10);
            }
            rgb_matrix_set_color(24, RGB_RED);
            rgb_matrix_set_color(21, RGB_GREEN);
            break;

        default:
            break;
    }
    return false;
}

void suspend_power_down_keymap(void) {
    rgb_matrix_set_suspend_state(true);
}

void suspend_wakeup_init_keymap(void) {
    rgb_matrix_set_suspend_state(false);
}

