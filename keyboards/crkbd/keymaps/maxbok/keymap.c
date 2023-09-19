/*
Copyright 2019 @foostan
Copyright 2020 Drashna Jaelre <@drashna>

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include QMK_KEYBOARD_H

#define SLSH_LM LT(_NUM_AND_NAV, KC_SLSH)
#define CTL_TAB CTL_T(KC_TAB)

enum layers {
    _QWERTY = 0,
    _NUM_AND_NAV = 1,
    _UTILS = 2
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [_QWERTY] = LAYOUT_split_3x6_3(
        KC_ESC,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,                          KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_BSPC,
        CTL_TAB, KC_A,    KC_S,    KC_D,    KC_F,    KC_G,                          KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_ENT,
        KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,                          KC_N,    KC_M,    KC_COMM, KC_DOT,  SLSH_LM, KC_RSFT,
                                            KC_LALT, KC_LCMD, MO(_UTILS),  KC_SPC,  KC_RCMD, KC_RALT
    ),
    [_NUM_AND_NAV] = LAYOUT_split_3x6_3(
        KC_GRV,  XXXXXXX, KC_P7,   KC_P8,   KC_P9,   XXXXXXX,                       XXXXXXX, KC_MPRV, KC_MPLY, KC_MNXT, KC_VOLD, KC_VOLU,
        _______, XXXXXXX, KC_P4,   KC_P5,   KC_P6,   XXXXXXX,                       KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT, XXXXXXX, XXXXXXX,
        _______, KC_P0,   KC_P1,   KC_P2,   KC_P3,   XXXXXXX,                       XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
                                            KC_LALT, KC_LCMD, XXXXXXX,     KC_SPC,  KC_RCMD, KC_RALT
    ),
    [_UTILS] = LAYOUT_split_3x6_3(
        KC_TILD, KC_EXLM, KC_AT,   KC_HASH, KC_DLR,  KC_PERC,                       KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN, _______,
        _______, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                       XXXXXXX, XXXXXXX, XXXXXXX, KC_LBRC, KC_RBRC, KC_BSLS,
        _______, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                       XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
                                            KC_LALT, KC_LCMD, _______,     KC_SPC,  KC_RCMD, KC_RALT
    )
};

#ifdef RGBLIGHT_ENABLE
void keyboard_post_init_user(void) {
    rgblight_enable_noeeprom(); // enables RGB, without saving settings
    rgblight_sethsv_noeeprom(HSV_CYAN); // sets the color to red without saving
    rgblight_mode_noeeprom(RGBLIGHT_MODE_BREATHING + 3); // sets mode to Fast breathing without saving
}

void matrix_init_user(void) {
    rgblight_enable_noeeprom(); // enables RGB, without saving settings
    rgblight_sethsv_noeeprom(HSV_CYAN); // sets the color to red without saving
    rgblight_mode_noeeprom(RGBLIGHT_MODE_BREATHING + 3); // sets mode to Fast breathing without saving
}

layer_state_t layer_state_set_keymap(layer_state_t state) {
    //rgblight_mode_noeeprom(RGBLIGHT_MODE_STATIC_LIGHT);
    switch (get_highest_layer(state)) {
        case _QWERTY:
            rgblight_sethsv_noeeprom(HSV_CYAN);
            break;
        case _NUM_AND_NAV:
            rgblight_sethsv_noeeprom(HSV_PURPLE);
            break;
        case _UTILS:
            rgblight_sethsv_noeeprom(HSV_GREEN);
            break;
        default:
            break;
    }
    return state;
}
#endif

#ifdef OLED_ENABLE
bool oled_task_user(void) {
    if (is_keyboard_master()) {
        oled_write_P(PSTR("Left"), false);
    } else {
        oled_write_P(PSTR("Right"), false);
    }
    return false;
}
#endif

