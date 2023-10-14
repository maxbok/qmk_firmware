#include "maxbok.h"

typedef uint16_t COLOR_SYMBOL;

#define ___ 0
#define NUM 10
#define SYM 20 // Symbol
#define UTL 50 // To utils
#define QBT 100 // Boot
#define BCK 110 // Back to base

#define COLOR_ORANGE        (RGB){ .r = 255, .g = 192, .b = 0   }
#define COLOR_DARK_ORANGE   (RGB){ .r = 255, .g = 80,  .b = 0   }

#define COLOR_RED           (RGB){ .r = 255, .g = 0,   .b = 0   }

#define COLOR_PURPLE        (RGB){ .r = 255, .g = 0,   .b = 255 }

#define COLOR_LIGHT_BLUE    (RGB){ .r = 35, .g = 65, .b = 200 }

#define COLOR_GREEN         (RGB){ .r = 0  , .g = 255, .b = 0   }

const uint16_t color_symbols[4][MATRIX_ROWS][MATRIX_COLS] = {
    [_QWERTY] = LAYOUT_split_3x6_3(
        ___, ___, ___, ___, ___, ___,               ___, ___, ___, ___, ___, ___,
        ___, ___, ___, ___, ___, ___,               ___, ___, ___, ___, ___, ___,
        ___, ___, ___, ___, ___, ___,               ___, ___, ___, ___, ___, ___,
                            ___, ___, ___,     ___, ___, ___
    ),
    [_SYMBOLS] = LAYOUT_split_3x6_3(
        ___, SYM, SYM, SYM, SYM, SYM,               SYM, SYM, SYM, SYM, SYM, ___,
        ___, NUM, NUM, NUM, NUM, NUM,               NUM, NUM, NUM, NUM, NUM, ___,
        ___, UTL, SYM, SYM, SYM, SYM,               ___, ___, ___, ___, ___, ___,
                            ___, ___, ___,     ___, ___, ___
    ),
    [_NAV] = LAYOUT_split_3x6_3(
        ___, ___, ___, ___, ___, ___,               ___, ___, ___, ___, ___, ___,
        ___, ___, ___, ___, ___, ___,               ___, ___, ___, ___, ___, ___,
        ___, ___, ___, ___, ___, ___,               ___, ___, ___, ___, ___, ___,
                            ___, ___, ___,     ___, ___, ___
    ),
    [_UTILS] = LAYOUT_split_3x6_3(
        QBT, ___, ___, ___, ___, ___,               ___, ___, ___, ___, ___, ___,
        ___, ___, ___, ___, ___, ___,               ___, ___, ___, ___, ___, ___,
        ___, BCK, ___, ___, ___, ___,               ___, ___, ___, ___, ___, ___,
                            ___, ___, ___,     ___, ___, ___
    )
};

RGB symbol_to_rgb(COLOR_SYMBOL symbol) {
    switch (symbol) {
        case NUM:   return COLOR_DARK_ORANGE;
        case SYM:   return COLOR_LIGHT_BLUE;
        case UTL:   return COLOR_PURPLE;
        case QBT:   return COLOR_RED;
        case BCK:   return COLOR_GREEN;
        default:    return (RGB) { RGB_OFF };
    }
}

bool rgb_matrix_indicators_advanced_user(uint8_t led_min, uint8_t led_max) {
    layer_state_t layer = get_highest_layer(layer_state);

    for (int row = 0; row < MATRIX_ROWS; row++) {
        for (int col = 0; col < MATRIX_COLS; col++) {
            uint8_t index = g_led_config.matrix_co[row][col];

            if (index >= led_min && index < led_max && index != NO_LED) {
                COLOR_SYMBOL symbol = color_symbols[layer][row][col];
                RGB rgb = symbol_to_rgb(symbol);
                rgb_matrix_set_color(index, rgb.r, rgb.g, rgb.b);
            }
        }
    }

    return false;
}

void suspend_power_down_keymap(void) {
    rgb_matrix_set_suspend_state(true);
}

void suspend_wakeup_init_keymap(void) {
    rgb_matrix_set_suspend_state(false);
}

