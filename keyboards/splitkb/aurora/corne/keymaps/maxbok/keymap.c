/* Copyright 2022 splitkb.com <support@splitkb.com>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include QMK_KEYBOARD_H

#define SLSH_LM LT(_NUM_AND_NAV, KC_SLSH)
#define CTL_TAB CTL_T(KC_TAB)

enum layers {
    _QWERTY = 0,
    _NUM_AND_NAV = 1
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [_QWERTY] = LAYOUT_split_3x6_3(
        KC_ESC,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,                          KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_BSPC,
        CTL_TAB, KC_A,    KC_S,    KC_D,    KC_F,    KC_G,                          KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_ENT,
        KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,                          KC_N,    KC_M,    KC_COMM, KC_DOT,  SLSH_LM, KC_RSFT,
                                            KC_LALT, KC_LCMD, XXXXXXX,     KC_SPC,  KC_RCMD, KC_RALT
    ),
    [_NUM_AND_NAV] =  LAYOUT_split_3x6_3(
        KC_GRV,  XXXXXXX, KC_P7,   KC_P8,   KC_P9,   XXXXXXX,                       KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_BSPC,
        CTL_TAB, XXXXXXX, KC_P4,   KC_P5,   KC_P6,   XXXXXXX,                       KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_ENT,
        KC_LSFT, KC_P0,   KC_P1,   KC_P2,   KC_P3,   XXXXXXX,                       KC_N,    KC_M,    KC_COMM, KC_DOT,  SLSH_LM, KC_RSFT,
                                            KC_LALT, KC_LCMD, XXXXXXX,     KC_SPC,  KC_RCMD, KC_RALT
    ),
};

#ifdef RGBLIGHT_ENABLE
void keyboard_post_init_user(void) {
  rgblight_enable_noeeprom(); // enables RGB, without saving settings
  rgblight_sethsv_noeeprom(HSV_RED); // sets the color to red without saving
  rgblight_mode_noeeprom(RGBLIGHT_MODE_BREATHING + 3); // sets mode to Fast breathing without saving
}
#endif

#ifdef OLED_ENABLE
bool oled_task_user(void) {
    // A 128x32 OLED rotated 90 degrees is 5 characters wide and 16 characters tall
    // This example string should fill that neatly
    const char *text = PSTR("abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ123456789!@#$%^&*()[]{}-=_+?");

    if (is_keyboard_master()) {
        oled_write_P(text, false);
    } else {
        oled_write_P(text, false);
    }
    return false;
}
#endif
