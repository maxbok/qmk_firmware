#ifdef RGB_MATRIX_CUSTOM_EFFECT_IMPLS

#include "maxbok.h"

// extern uint16_t COLOR_SYMBOL;
extern const uint16_t color_symbols[4][MATRIX_ROWS][MATRIX_COLS];
extern RGB symbol_to_rgb(uint16_t);

// Still effect

void turn_off_underglow(void) {
    RGB color = (RGB) { RGB_OFF };
    for (uint8_t i = 0; i < 6; i++) {
        rgb_matrix_set_color(i, color.r, color.g, color.b);
    }
    for (uint8_t i = 27; i < 33; i++) {
        rgb_matrix_set_color(i, color.r, color.g, color.b);
    }
}

static bool still_effect(uint16_t layer, effect_params_t* params) {
    turn_off_underglow();

    RGB_MATRIX_USE_LIMITS(led_min, led_max);

    for (int row = 0; row < MATRIX_ROWS; row++) {
        for (int col = 0; col < MATRIX_COLS; col++) {
            uint8_t index = g_led_config.matrix_co[row][col];

            if (index >= led_min &&
                index < led_max &&
                HAS_ANY_FLAGS(g_led_config.flags[index], params->flags)) {
                uint16_t symbol = color_symbols[layer][row][col];
                RGB rgb = symbol_to_rgb(symbol);
                rgb_matrix_set_color(index, rgb.r, rgb.g, rgb.b);
            }
        }
    }

    return rgb_matrix_check_finished_leds(led_max);
}

// Qwerty
static bool QWERTY(effect_params_t* params) {
    return still_effect(_QWERTY, params);
}

// Symbols
static bool SYMBOLS(effect_params_t* params) {
    return still_effect(_SYMBOLS, params);
}

// Nav
static bool NAV(effect_params_t* params) {
    return still_effect(_NAV, params);
}

// Utils
static bool UTILS(effect_params_t* params) {
    return still_effect(_UTILS, params);
}

#endif
