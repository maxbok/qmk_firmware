/*
Copyright 2016 Daniel Svensson <dsvensson@gmail.com>

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

#define KM_QWERTY  0
#define KM_MEDIA   1

#define SLSH_LM LT(KM_MEDIA, KC_SLSH)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  /* Layer 0: Standard ISO layer */
  [KM_QWERTY] = LAYOUT( \
    XXXXXXX,          XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,    XXXXXXX, XXXXXXX, XXXXXXX, \
    KC_ESC,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS, KC_EQL,  KC_BSPC,    XXXXXXX, XXXXXXX, XXXXXXX, \
    KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_LBRC, KC_RBRC, KC_BSLS,    XXXXXXX, XXXXXXX, XXXXXXX, \
    KC_LCTL, KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT,          KC_ENT,                                \
    KC_LSFT, KC_NUBS, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  SLSH_LM,          KC_RSFT,             KC_UP,            \
    KC_LCTL, KC_LALT, KC_LCMD,                            KC_SPC,                             KC_RCMD, KC_RALT, MO(1),   TT(1),      KC_LEFT, KC_DOWN, KC_RGHT  \
  ),
  /* Layer 1: Function layer */
  [KM_MEDIA] = LAYOUT( \
    _______,          _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,    KC_WAKE, KC_PWR,  KC_SLEP, \
    KC_GRV,  _______, _______, _______, _______, _______, _______, _______, KC_VOLD, KC_VOLU, _______, _______, _______, _______,    _______, _______, _______, \
    _______, _______, _______, _______, RESET,   _______, _______, KC_MPRV, KC_MPLY, KC_MNXT, _______, _______, _______, _______,    _______, _______, _______, \
    _______, _______, _______, _______, _______, _______, KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT, _______, _______,          _______,                               \
    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          _______,             _______,          \
    _______, _______, _______,                            _______,                            _______, _______, _______, _______,    _______, _______, _______  \
  )
};

void keyboard_post_init_user(void) {
    uint8_t time = 75;

    for (int i = 0; i < 2; i++) {
        ph_caps_led_on();
        wait_ms(time);
        ph_caps_led_off();

        ph_sclk_led_on();
        wait_ms(time);
        ph_sclk_led_off();
    }

    wait_ms(4 * time);

    ph_caps_led_on();
    ph_sclk_led_on();
    wait_ms(time);
    ph_caps_led_off();
    ph_sclk_led_off();
}

uint32_t layer_state_set_user(uint32_t state) {
    switch(biton32(state)) {
        case KM_QWERTY:
            ph_caps_led_off();
            ph_sclk_led_off();
            break;
        case KM_MEDIA:
            ph_caps_led_on();
            ph_sclk_led_on();
            break;
    }
    return state;
}

