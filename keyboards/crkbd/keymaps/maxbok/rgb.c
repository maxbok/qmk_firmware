#include "rgb.h"

layer_state_t layer_state_set_user(layer_state_t state) {
    switch (biton32(state)) {
        case _QWERTY:
            rgb_matrix_mode_noeeprom(RGB_MATRIX_CUSTOM_QWERTY);
            break;
        case _SYMBOLS:
            rgb_matrix_mode_noeeprom(RGB_MATRIX_CUSTOM_SYMBOLS);
            break;
        case _NAV:
            rgb_matrix_mode_noeeprom(RGB_MATRIX_CUSTOM_NAV);
            break;
        case _UTILS:
            rgb_matrix_mode_noeeprom(RGB_MATRIX_CUSTOM_UTILS);
            break;
        default:
            rgb_matrix_mode_noeeprom(RGB_MATRIX_SOLID_COLOR);
            rgb_matrix_sethsv_noeeprom(HSV_RED);
            break;
    }

    return state;
}

void suspend_power_down_keymap(void) {
    rgb_matrix_set_suspend_state(true);
}

void suspend_wakeup_init_keymap(void) {
    rgb_matrix_set_suspend_state(false);
}

