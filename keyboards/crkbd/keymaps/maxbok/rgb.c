#include "rgb.h"

void rgb_keyboard_init(void) {
    rgb_matrix_enable_noeeprom();
    rgb_matrix_set_color_all(RGB_WHITE);
    rgb_matrix_mode_noeeprom(RGB_MATRIX_SOLID_COLOR);
}

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

#define ___ 0
#define BLE 1
#define WHT 2
#define GRY 3
#define LPL 4
#define DPL 5
#define NUM 10
#define SYM 20 // Symbol
#define NAV 30
#define MOU 40
#define UTL 50 // To utils
#define QBT 100 // Boot


#define COLOR_WHITE         (RGB){ .r = 255, .g = 255, .b = 255 } 
#define COLOR_GRAY          (RGB){ .r = 150, .g = 150, .b = 150 } 
#define COLOR_LIGHT_PURPLE  (RGB){ .r = 147, .g = 112, .b = 219 } 
#define COLOR_DARK_PURPLE   (RGB){ .r = 73,  .g = 56,  .b = 109 } 

#define COLOR_ORANGE        (RGB){ .r = 255, .g = 192, .b = 0   }
#define COLOR_DARK_ORANGE   (RGB){ .r = 255, .g = 80,  .b = 0   }

#define COLOR_RED           (RGB){ .r = 255, .g = 0,   .b = 0   }
#define COLOR_LIGHT_RED     (RGB){ .r = 255, .g = 25,  .b = 25  }

#define COLOR_LIGHT_BLUE    (RGB){ .r = 35,  .g = 65,  .b = 200 }
#define COLOR_BLUE          (RGB){ .r = 20,  .g = 30,  .b = 255 }


RGB symbol_to_rgb(COLOR_SYMBOL symbol) {
    switch (symbol) {
        case BLE:   return COLOR_LIGHT_BLUE;
        case WHT:   return COLOR_WHITE;
        case GRY:   return COLOR_GRAY;
        case LPL:   return COLOR_LIGHT_PURPLE;
        case DPL:   return COLOR_DARK_PURPLE;

        case NUM:   return COLOR_DARK_PURPLE;
        case SYM:   return COLOR_LIGHT_PURPLE;
        case NAV:   return COLOR_BLUE;
        case MOU:   return COLOR_LIGHT_BLUE;
        case UTL:   return COLOR_LIGHT_RED;
        case QBT:   return COLOR_RED;

        default:    return (RGB) { RGB_OFF };
    }
}

const uint16_t color_symbols[4][MATRIX_ROWS][MATRIX_COLS] = {
    // [_QWERTY] = LAYOUT_split_3x6_3(
    //     BLE, WHT, WHT, WHT, WHT, GRY,               GRY, LPL, LPL, DPL, DPL, DPL,
    //     WHT, WHT, WHT, WHT, GRY, GRY,               LPL, LPL, DPL, DPL, DPL, DPL,
    //     WHT, WHT, WHT, GRY, GRY, LPL,               LPL, DPL, DPL, DPL, DPL, DPL,
    //                         GRY, LPL, LPL,     LPL, DPL, DPL
    // ),
    [_QWERTY] = LAYOUT_split_3x6_3(
        ___, ___, ___, ___, ___, ___,               ___, ___, ___, ___, ___, ___,
        ___, ___, ___, ___, ___, ___,               ___, ___, ___, ___, ___, ___,
        ___, ___, ___, ___, ___, ___,               ___, ___, ___, ___, ___, ___,
                            ___, ___, ___,     ___, ___, ___
    ),
    [_SYMBOLS] = LAYOUT_split_3x6_3(
        ___, SYM, SYM, SYM, SYM, SYM,               SYM, SYM, SYM, SYM, SYM, ___,
        ___, NUM, NUM, NUM, NUM, NUM,               NUM, NUM, NUM, NUM, NUM, ___,
        ___, UTL, SYM, SYM, SYM, SYM,               ___, ___, ___, ___, UTL, ___,
                            ___, ___, ___,     ___, ___, ___
    ),
    [_NAV] = LAYOUT_split_3x6_3(
        ___, ___, ___, MOU, ___, ___,               ___, ___, ___, ___, ___, ___,
        ___, ___, MOU, MOU, MOU, ___,               NAV, NAV, NAV, NAV, ___, ___,
        ___, ___, ___, MOU, ___, ___,               ___, ___, ___, ___, ___, ___,
                            ___, ___, ___,     ___, ___, ___
    ),
    [_UTILS] = LAYOUT_split_3x6_3(
        ___, ___, ___, ___, ___, QBT,               QBT, ___, ___, ___, ___, ___,
        ___, ___, ___, ___, ___, ___,               ___, ___, ___, ___, ___, ___,
        ___, UTL, ___, ___, ___, ___,               ___, ___, ___, ___, UTL, ___,
                            ___, ___, ___,     ___, ___, ___
    )
};

