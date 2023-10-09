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

static void render_logo(void) {
    static const char PROGMEM logo[] = {
        // 'Star wars', 32x128px
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0xe1, 0x01, 0x18, 0x1c, 0x9e, 0x9f, 0x9f, 0x9f, 0x9f, 
        0x9f, 0x9f, 0x93, 0x93, 0x9a, 0x1c, 0x18, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x7e, 0x7e, 0xfc, 0xfc, 0xf0, 0xc0, 0x00, 0xff, 
        0xff, 0x00, 0x80, 0xf0, 0xf8, 0xfc, 0x7e, 0x7e, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x01, 0x00, 0x01, 
        0x01, 0x00, 0x01, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0xc0, 0xc0, 0x00, 
        0xa0, 0x00, 0x40, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x70, 0xf0, 0x00, 0xf9, 0x01, 0x00, 0x00, 
        0x01, 0x00, 0x00, 0xf9, 0xf1, 0x00, 0xf0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xbe, 0x00, 0x3f, 0x2f, 0x0f, 0x88, 
        0x88, 0x3f, 0x3f, 0x3f, 0x1f, 0xbe, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x01, 0x01, 0x00, 0x00, 0x00, 0x01, 
        0x01, 0x00, 0x00, 0x00, 0x00, 0x01, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 
        0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xf0, 0xeb, 0x8b, 0x8b, 0x8b, 0xcb, 0xeb, 0xfb, 
        0xfb, 0xeb, 0xcb, 0x8b, 0x8b, 0x8b, 0xcb, 0xf0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x02, 0x0f, 0x1f, 0xff, 0xff, 0xfb, 0xf9, 0xfd, 0x1c, 0x1c, 
        0x1c, 0x1c, 0xfd, 0xf9, 0xfb, 0xff, 0xff, 0x1f, 0x0f, 0x02, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x01, 0x00, 0x00, 0x00, 
        0x00, 0x00, 0x00, 0x01, 0x01, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x40, 0x40, 0xc0, 0xc0, 
        0xc0, 0xc0, 0xc0, 0x40, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x70, 0x3c, 0x3f, 0x30, 0x20, 0x60, 0x60, 0x20, 0x39, 
        0x3f, 0x3f, 0x3f, 0x3f, 0x34, 0x64, 0x40, 0x60, 0x60, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x07, 0x1f, 0x3f, 0x7f, 0x7f, 0xff, 0xff, 0xff, 0xff, 
        0xff, 0xff, 0x7f, 0x7f, 0x37, 0x23, 0x01, 0x01, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x01, 
        0x01, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
    };

    oled_write_raw_P(logo, sizeof(logo));
}

bool oled_task_user(void) {
    if (is_keyboard_master()) {
        //oled_render_layer_state();
        // char *string = displayCharacters(leftCharacters[_QWERTY]);
        // oled_write_P(PSTR(string), false);
        // free(string);

        //oled_write_P(PSTR("Corne"), false);

        render_logo();
    } else {
        // oled_write_P(PSTR("yuiopB\nhjkl'E\nnm,./S\nSCA"), false);
    }

    return false;
}

