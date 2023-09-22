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

enum layers {
    _QWERTY = 0,
    _SYMBOLS = 1,
    _NAV = 2,
};

#define SLSH_LM LT(_NAV, KC_SLSH)
#define CTL_TAB CTL_T(KC_TAB)
#define SPC_SYM LT(_SYMBOLS, KC_SPC)

#define PRV_TAB SCMD(KC_LCBR)
#define NXT_TAB SCMD(KC_RCBR)
#define WEB_PRV LCMD(KC_LBRC)
#define WEB_NXT LCMD(KC_RBRC)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [_QWERTY] = LAYOUT_split_3x6_3(
        KC_ESC,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,                               KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_BSPC,
        CTL_TAB, KC_A,    KC_S,    KC_D,    KC_F,    KC_G,                               KC_H,    KC_J,    KC_K,    KC_L,    KC_QUOT, KC_ENT,
        KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,                               KC_N,    KC_M,    KC_COMM, KC_DOT,  SLSH_LM, KC_RSFT,
                                            KC_LALT, KC_LCMD, MO(_SYMBOLS),     SPC_SYM, KC_RCMD, KC_RALT
    ),
    [_SYMBOLS] = LAYOUT_split_3x6_3(
        KC_GRV,  KC_EXLM, KC_AT,   KC_HASH, KC_DLR,  KC_PERC,                            KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN, KC_DEL,
        _______, KC_1,    KC_2,    KC_3,    KC_4,    KC_5,                               KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_BSLS,
        _______, XXXXXXX, KC_SCLN, KC_MINS, KC_EQL,  KC_COLN,                            KC_LBRC, KC_RBRC, XXXXXXX, XXXXXXX, XXXXXXX, _______,
                                            _______, _______, _______,          _______, _______, _______
    ),
    [_NAV] = LAYOUT_split_3x6_3(
        KC_GRV,  KC_BRMD, KC_BRMU, XXXXXXX, KC_VOLD, KC_VOLU,                            XXXXXXX, KC_MPRV, KC_MPLY, KC_MNXT, XXXXXXX, XXXXXXX,
        _______, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                            KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT, XXXXXXX, XXXXXXX,
        _______, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                            WEB_PRV, PRV_TAB, NXT_TAB, WEB_NXT, XXXXXXX, XXXXXXX,
                                            _______, _______, _______,          _______, _______, _______
    ),
};

void keyboard_post_init_user(void) {
#ifdef RGB_MATRIX_ENABLE
    // rgblight_enable_noeeprom(); // enables RGB, without saving settings
    // rgblight_mode_noeeprom(ENABLE_RGB_MATRIX_GRADIENT_UP_DOWN); // sets mode to Fast breathing without saving
    // rgblight_sethsv_noeeprom(HSV_OFF);
    eeconfig_update_rgb_matrix_default();
    rgb_matrix_enable();
#endif
}

#ifdef RGB_MATRIX_ENABLE
layer_state_t layer_state_set_user(layer_state_t state) {
    switch (get_highest_layer(state)) {
        case _QWERTY:
            rgblight_sethsv_noeeprom(HSV_OFF);
            break;
        case _SYMBOLS:
            rgblight_sethsv_noeeprom(HSV_ORANGE);
            break;
        case _NAV:
            rgblight_sethsv_noeeprom(HSV_TEAL);
            break;
        default:
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
#endif

#ifdef OLED_ENABLE
static void oled_render_layer_state(void) {
    oled_write_P(PSTR("Layer: "), false);
    switch (get_highest_layer(layer_state)) {
        case _QWERTY:
            oled_write_ln_P(PSTR("Base"), false);
            break;
        case _SYMBOLS:
            oled_write_ln_P(PSTR("Symbols"), false);
            break;
        case _NAV:
            oled_write_ln_P(PSTR("Navigation"), false);
            break;
        default:
            oled_write_ln_P(PSTR("Oops"), false);
            break;
    }
}

bool oled_task_user(void) {
    if (is_keyboard_master()) {
        oled_render_layer_state();
        return false;
    }

    return true;
}
#endif

