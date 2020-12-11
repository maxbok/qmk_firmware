/* Copyright 2018 Yiancar
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
#include "action_tapping.h"
#include "keyboards/wilba_tech/wt_rgb_backlight.h"
#include "drivers/issi/is31fl3733.h"

//This is the ANSI version of the PCB

#define SLSH_LM LT(1, KC_SLSH)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [0] = LAYOUT_60_ansi( /* Base */
    KC_ESC,   KC_1,     KC_2,     KC_3,     KC_4,     KC_5,     KC_6,     KC_7,     KC_8,     KC_9,     KC_0,     KC_MINS,  KC_EQL,  KC_BSPC, \
    KC_TAB,   KC_Q,     KC_W,     KC_E,     KC_R,     KC_T,     KC_Y,     KC_U,     KC_I,     KC_O,     KC_P,     KC_LBRC,  KC_RBRC, KC_BSLS, \
    KC_LCTL,  KC_A,     KC_S,     KC_D,     KC_F,     KC_G,     KC_H,     KC_J,     KC_K,     KC_L,     KC_SCLN,  KC_QUOT,           KC_ENT,  \
    KC_LSFT,            KC_Z,     KC_X,     KC_C,     KC_V,     KC_B,     KC_N,     KC_M,     KC_COMM,  KC_DOT,   SLSH_LM,           KC_RSFT, \
    KC_LCTL,  KC_LALT,  KC_LCMD,                                KC_SPC,                                 KC_RCMD,  KC_RALT,  KC_RCTL, MO(2)    \
  ),

  [1] = LAYOUT_60_ansi( /* Utils */
    KC_GRV,   XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  KC_VOLD,  KC_VOLU,  XXXXXXX,  XXXXXXX,  XXXXXXX, XXXXXXX, \
    _______,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  KC_MPRV,  KC_MPLY,  KC_MNXT,  XXXXXXX,  XXXXXXX,  XXXXXXX, XXXXXXX, \
    _______,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  KC_LEFT,  KC_DOWN,  KC_UP,    KC_RGHT,  XXXXXXX,  XXXXXXX,           _______, \
    _______,            XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,           _______, \
    _______,  _______,  _______,                                XXXXXXX,                                _______,  _______,  _______, _______  \
  ),

  [2] = LAYOUT_60_ansi( /* Function */
    XXXXXXX,  KC_BRMD,  KC_BRMU,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX, KC_DEL , \
    XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  RESET,   XXXXXXX, \
    XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  S1_DEC,   S1_INC,   S2_DEC,   S2_INC,   XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,           XXXXXXX, \
    XXXXXXX,            EF_DEC,   EF_INC,   H1_DEC,   H1_INC,   H2_DEC,   H2_INC,   BR_DEC,   BR_INC,   ES_DEC,   ES_INC,            XXXXXXX, \
    XXXXXXX,  XXXXXXX,  XXXXXXX,                                XXXXXXX,                                XXXXXXX,  XXXXXXX,  XXXXXXX, XXXXXXX  \
  ),
};

const uint8_t ledIndexes[DRIVER_LED_TOTAL] = {
    0,        4,        8,        12,       16,       20,       24,       28,       32,       36,       40,       44,       48,      52,
    1,        5,        9,        13,       17,       21,       25,       29,       33,       37,       41,       45,       49,      53,
    2,        6,        10,       14,       18,       22,       26,       30,       34,       38,       42,       46,                54,
    3,                  7,        11,       15,       19,       23,       27,       31,       35,       39,       43,                51,
    56,       57,       58,                                     59,                                     61,       62,       63,      55
};

#define NAV 10
#define M_NAV 20
#define M_VOL 30
#define BRIGHTN 40
#define DANGER 50

const uint8_t utilsColors[] = {
    _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  M_VOL,    M_VOL,    _______,  _______,  _______, _______,
    _______,  _______,  _______,  _______,  _______,  _______,  _______,  M_NAV,    M_NAV,    M_NAV,    _______,  _______,  _______, _______,
    _______,  _______,  _______,  _______,  _______,  _______,  NAV,      NAV,      NAV,      NAV,      _______,  _______,           _______,
    _______,            _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,           _______,
    _______,  _______,  _______,                                _______,                                _______,  _______,  _______, _______
};

const uint8_t functionColors[] = {
    _______,  BRIGHTN,  BRIGHTN,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______, _______,
    _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  DANGER,  _______,
    _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,           _______,
    _______,            _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,           _______,
    _______,  _______,  _______,                                _______,                                _______,  _______,  _______, _______
};

void keyboard_post_init_user(void) {
}

RGB colorAt(uint8_t index, const uint8_t colors[]) {
    switch (colors[index]) {
        case NAV:         return (RGB){ .r = 0,   .g = 255, .b = 0   };
        case M_NAV:       return (RGB){ .r = 0,   .g = 255, .b = 255 };
        case M_VOL:       return (RGB){ .r = 255, .g = 255, .b = 0   };
        case BRIGHTN:     return (RGB){ .r = 0,   .g = 255, .b = 255 };
        case DANGER:      return (RGB){ .r = 255, .g = 0,   .b = 0   };
        case _______:     return (RGB){ .r = 0,   .g = 0,   .b = 0   };
        default:          return (RGB){ .r = 0,   .g = 0,   .b = 0   };
    }
}

uint32_t layer_state_set_user(uint32_t state) {
    switch(biton32(state)) {
        case 0:
            backlight_timer_enable();
            break;
        case 1:
            backlight_timer_disable();

            for (uint8_t i = 0; i < DRIVER_LED_TOTAL; i++) {
                RGB rgb = colorAt(i, utilsColors);
                uint8_t index = ledIndexes[i];
                IS31FL3733_set_color(index, rgb.r, rgb.g, rgb.b);
            }
            break;
        case 2:
            backlight_timer_disable();

            for (uint8_t i = 0; i < DRIVER_LED_TOTAL; i++) {
                RGB rgb = colorAt(i, functionColors);
                uint8_t index = ledIndexes[i];
                IS31FL3733_set_color(index, rgb.r, rgb.g, rgb.b);
            }
            break;
    }

    return state;
}

void matrix_init_user(void) {
  //user initialization
}

void matrix_scan_user(void) {
  //user matrix
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  return true;
}

uint16_t get_tapping_term(uint16_t keycode) {
  switch (keycode) {
    case SLSH_LM:
      return 150;
    default:
      return TAPPING_TERM;
  }
}

