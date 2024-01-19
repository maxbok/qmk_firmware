#ifdef RGB_MATRIX_CUSTOM_EFFECT_IMPLS

#include "maxbok.h"

// extern uint16_t COLOR_SYMBOL;
extern const uint16_t color_symbols[4][MATRIX_ROWS][MATRIX_COLS];
extern RGB symbol_to_rgb(uint16_t);

// Still effect

static bool still_effect(uint16_t layer, effect_params_t* params) {
    RGB color = (RGB) { RGB_OFF };
    rgb_matrix_set_color(0, color.r, color.g, color.b);
    rgb_matrix_set_color(1, color.r, color.g, color.b);
    rgb_matrix_set_color(2, color.r, color.g, color.b);
    rgb_matrix_set_color(3, color.r, color.g, color.b);
    rgb_matrix_set_color(4, color.r, color.g, color.b);
    rgb_matrix_set_color(5, color.r, color.g, color.b);
    rgb_matrix_set_color(27, color.r, color.g, color.b);
    rgb_matrix_set_color(28, color.r, color.g, color.b);
    rgb_matrix_set_color(29, color.r, color.g, color.b);
    rgb_matrix_set_color(30, color.r, color.g, color.b);
    rgb_matrix_set_color(31, color.r, color.g, color.b);
    rgb_matrix_set_color(32, color.r, color.g, color.b);

    RGB_MATRIX_USE_LIMITS(led_min, led_max);

    for (int row = 0; row < MATRIX_ROWS; row++) {
        for (int col = 0; col < MATRIX_COLS; col++) {
            uint8_t index = g_led_config.matrix_co[row][col];

            if (index >= led_min && index < led_max && index != NO_LED) {
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
