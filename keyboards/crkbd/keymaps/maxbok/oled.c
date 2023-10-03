#include "maxbok.h"

// char *leftCharacters[][MATRIX_ROWS] = {
//     [_QWERTY] = { "↖qwert", "^asdfg", "⇧zxcvb", "    ⌥⌘S" }
// };
// 
// char *displayCharacters(char *charArray[MATRIX_ROWS]) {
//     int length = 0;
// 
//     for (int i = 0; i < MATRIX_ROWS; i++) {
//         length += strlen(charArray[i]);
//     }
// 
//     char *string = malloc(sizeof(char) * length);
// 
//     for (int i = 0; i < MATRIX_ROWS; i++) {
//         strcat(string, "\n");
//         strcat(string, charArray[i]);
//     } 
// 
//     return string;
// }
//
// static char rightCharacters[][MATRIX_ROWS][MATRIX_COLS] = {
//     [_QWERTY] = {
//         {"yuiop←"}, 
//         {"hjkl'↩"},
//         {"nm,./⇧"},
//         {"␣⌘⌥"}
//     }
// };

// static void oled_render_layer_state(void) {
//     oled_write_P(PSTR("Layer: \n"), false);
//     switch (get_highest_layer(layer_state)) {
//         case _QWERTY:
//             oled_write_ln_P(PSTR("Base"), false);
//             break;
//         case _SYMBOLS:
//             oled_write_ln_P(PSTR("Symbols"), false);
//             break;
//         case _NAV:
//             oled_write_ln_P(PSTR("Navigation"), false);
//             break;
//         default:
//             oled_write_ln_P(PSTR("Oops"), false);
//             break;
//     }
// }

oled_rotation_t oled_init_user(oled_rotation_t rotation) {
    if (is_keyboard_master()) {
        return OLED_ROTATION_270;
    } else {
        return OLED_ROTATION_90;
    }
}

bool oled_task_user(void) {
    if (is_keyboard_master()) {
        //oled_render_layer_state();
        // char *string = displayCharacters(leftCharacters[_QWERTY]);
        // oled_write_P(PSTR(string), false);
        // free(string);

        oled_write_P(PSTR("Corne"), false);
    } else {
        // oled_write_P(PSTR("yuiopB\nhjkl'E\nnm,./S\nSCA"), false);
    }

    return false;
}

