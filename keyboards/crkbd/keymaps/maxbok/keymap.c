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

#include "maxbok.h"
#include "rgb.h"
#include "oled.h"

#define SLSH_LM LT(_NAV, KC_SLSH)
#define CTL_TAB CTL_T(KC_TAB)
#define SFT_DEL RSFT_T(KC_DEL)
#define SPC_SYM LT(_SYMBOLS, KC_SPC)
#define MO_SYM  MO(_SYMBOLS)
#define TO_UTIL OSL(_UTILS)

#define PRV_TAB SCMD(KC_LCBR)
#define NXT_TAB SCMD(KC_RCBR)
#define WEB_PRV LCMD(KC_LBRC)
#define WEB_NXT LCMD(KC_RBRC)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [_QWERTY] = LAYOUT_split_3x6_3(
        KC_ESC,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,                        KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_BSPC,
        CTL_TAB, KC_A,    KC_S,    KC_D,    KC_F,    KC_G,                        KC_H,    KC_J,    KC_K,    KC_L,    KC_QUOT, KC_ENT,
        KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,                        KC_N,    KC_M,    KC_COMM, KC_DOT,  SLSH_LM, SFT_DEL,
                                            KC_LALT, KC_LCMD, MO_SYM,    SPC_SYM, KC_RCMD, KC_RALT
    ),
    [_SYMBOLS] = LAYOUT_split_3x6_3(
        KC_GRV,  KC_EXLM, KC_AT,   KC_HASH, KC_DLR,  KC_PERC,                     KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN, _______,
        _______, KC_1,    KC_2,    KC_3,    KC_4,    KC_5,                        KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_BSLS,
        _______, TO_UTIL, KC_SCLN, KC_COLN, KC_MINS, KC_EQL,                      KC_LCBR, KC_LBRC, KC_RBRC, KC_RCBR, TO_UTIL, _______,
                                            _______, _______, _______,   _______, _______, _______
    ),
    [_NAV] = LAYOUT_split_3x6_3(
        KC_GRV,  KC_BRMD, KC_BRMU, KC_MS_U, KC_VOLD, KC_VOLU,                     XXXXXXX, KC_MPRV, KC_MPLY, KC_MNXT, XXXXXXX, XXXXXXX,
        _______, XXXXXXX, KC_MS_L, KC_BTN1, KC_MS_R, XXXXXXX,                     KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT, XXXXXXX, XXXXXXX,
        _______, XXXXXXX, XXXXXXX, KC_MS_D, XXXXXXX, XXXXXXX,                     WEB_PRV, PRV_TAB, NXT_TAB, WEB_NXT, XXXXXXX, XXXXXXX,
                                            _______, _______, _______,   _______, _______, _______
    ),
    [_UTILS] = LAYOUT_split_3x6_3(
        XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, QK_BOOT,                     QK_BOOT, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
        XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                     XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
        XXXXXXX, TG_UTIL, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                     XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, TG_UTIL, XXXXXXX,
                                            XXXXXXX, XXXXXXX, XXXXXXX,   XXXXXXX, XXXXXXX, XXXXXXX
    )
};

void keyboard_post_init_user(void) {
    rgb_keyboard_init();
    oled_keyboard_init();
}

uint16_t get_tapping_term(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case SLSH_LM:
            return 150;
        case CTL_TAB:
            return 140;
        case SFT_DEL:
            return 100;
        case SPC_SYM:
            return 200;
        default:
            return TAPPING_TERM;
    }
}

bool get_permissive_hold(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case SLSH_LM:
        case CTL_TAB:
        case SFT_DEL:
            return true;
        default:
            return false;
    }
}

uint16_t get_quick_tap_term(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case SLSH_LM:
        case SFT_DEL:
            return 0;
        default:
            return get_tapping_term(keycode, record);
    }
}

