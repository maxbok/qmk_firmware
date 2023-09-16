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
#include "drivers/led/issi/is31fl3733.h"

//This is the ANSI version of the PCB

#define SLSH_LM LT(1, KC_SLSH)
#define CTL_TAB CTL_T(KC_TAB)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [0] = LAYOUT_60_ansi( /* Base */
    KC_ESC,   KC_1,     KC_2,     KC_3,     KC_4,     KC_5,     KC_6,     KC_7,     KC_8,     KC_9,     KC_0,     KC_MINS,  KC_EQL,   KC_BSPC, \
    KC_TAB,   KC_Q,     KC_W,     KC_E,     KC_R,     KC_T,     KC_Y,     KC_U,     KC_I,     KC_O,     KC_P,     KC_LBRC,  KC_RBRC,  KC_BSLS, \
    CTL_TAB,  KC_A,     KC_S,     KC_D,     KC_F,     KC_G,     KC_H,     KC_J,     KC_K,     KC_L,     KC_SCLN,  KC_QUOT,            KC_ENT,  \
    KC_LSFT,            KC_Z,     KC_X,     KC_C,     KC_V,     KC_B,     KC_N,     KC_M,     KC_COMM,  KC_DOT,   SLSH_LM,            KC_RSFT, \
    KC_LCTL,  KC_LALT,  KC_LCMD,                                KC_SPC,                                 KC_RCMD,  KC_RALT,  TG(3),    MO(2)    \
  ),

  [1] = LAYOUT_60_ansi( /* Utils */
    KC_GRV,   XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  KC_VOLD,  KC_VOLU,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX, \
    _______,  XXXXXXX,  KC_7,     KC_8,     KC_9,     XXXXXXX,  XXXXXXX,  KC_MPRV,  KC_MPLY,  KC_MNXT,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX, \
    _______,  XXXXXXX,  KC_4,     KC_5,     KC_6,     XXXXXXX,  KC_LEFT,  KC_DOWN,  KC_UP,    KC_RGHT,  XXXXXXX,  XXXXXXX,            _______, \
    _______,            KC_0,     KC_1,     KC_2,     KC_3,     XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,            _______, \
    _______,  _______,  _______,                                XXXXXXX,                                _______,  _______,  _______,  _______  \
  ),

  [2] = LAYOUT_60_ansi( /* Function */
    XXXXXXX,  KC_BRMD,  KC_BRMU,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  KC_DEL,  \
    XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  QK_BOOT,  XXXXXXX, \
    XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  S1_DEC,   S1_INC,   S2_DEC,   S2_INC,   XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,            XXXXXXX, \
    XXXXXXX,            EF_DEC,   EF_INC,   H1_DEC,   H1_INC,   H2_DEC,   H2_INC,   BR_DEC,   BR_INC,   ES_DEC,   ES_INC,             XXXXXXX, \
    XXXXXXX,  XXXXXXX,  XXXXXXX,                                XXXXXXX,                                XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX  \
  ),

  [3] = LAYOUT_60_ansi( /* Test layer */
    XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX, \
    XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX, \
    XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,            XXXXXXX, \
    XXXXXXX,            XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,            XXXXXXX, \
    XXXXXXX,  XXXXXXX,  XXXXXXX,                                XXXXXXX,                                XXXXXXX,  XXXXXXX,  TG(3),    XXXXXXX  \
  ),
};

#define LED_MATRIX_COUNT 61

const uint8_t ledIndexes[LED_MATRIX_COUNT] = {
    0,        4,        8,        12,       16,       20,       24,       28,       32,       36,       40,       44,       48,       52,
    1,        5,        9,        13,       17,       21,       25,       29,       33,       37,       41,       45,       49,       53,
    2,        6,        10,       14,       18,       22,       26,       30,       34,       38,       42,       46,                 54,
    3,                  7,        11,       15,       19,       23,       27,       31,       35,       39,       43,                 51,
    56,       57,       58,                                     59,                                     61,       62,       63,       55
};

#define NAV 10
#define M_NAV 20
#define M_VOL 30
#define KEYPAD 40
#define BRIGHTN 100
#define LED_ACT 110
#define DANGER 120

#define WHITE   200
#define RED     210
#define ORANGE  220
#define BLUE1   230
#define BLUE2   231
#define BLUE3   232

#define COLOR_WHITE     (RGB){ .r = 200, .g = 255, .b = 255 }
#define COLOR_RED       (RGB){ .r = 255, .g = 0,   .b = 0   }
#define COLOR_ORANGE    (RGB){ .r = 255, .g = 192, .b = 0   }
#define COLOR_BLUE1     (RGB){ .r = 0,   .g = 0,   .b = 255 }
#define COLOR_BLUE2     (RGB){ .r = 15,  .g = 72,  .b = 255 }
#define COLOR_BLUE3     (RGB){ .r = 30,  .g = 144, .b = 255 }

const uint16_t initColors[] = {
    _______,  _______,  _______,  _______,  _______,  BLUE1,    BLUE1,    BLUE1,    BLUE1,    BLUE1,    BLUE1,    BLUE1,    BLUE1,    BLUE1,  
    _______,  _______,  _______,  _______,  BLUE2,    BLUE2,    BLUE2,    BLUE2,    BLUE2,    BLUE2,    BLUE2,    BLUE2,    BLUE2,    BLUE2,    
    _______,  _______,  _______,  BLUE3,    BLUE3,    BLUE3,    BLUE3,    BLUE3,    BLUE3,    BLUE3,    BLUE3,    BLUE3,              BLUE3,
    _______,            _______,  ORANGE,   ORANGE,   ORANGE,   ORANGE,   ORANGE,   ORANGE,   ORANGE,   ORANGE,   ORANGE,             ORANGE, 
    _______,  _______,  RED,                                    RED,                                    RED,      RED,      RED,      RED
};

const uint16_t utilsColors[] = {
    _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  M_VOL,    M_VOL,    _______,  _______,  _______,  _______,
    _______,  _______,  KEYPAD,   KEYPAD,   KEYPAD,   _______,  _______,  M_NAV,    M_NAV,    M_NAV,    _______,  _______,  _______,  _______,
    _______,  _______,  KEYPAD,   KEYPAD,   KEYPAD,   _______,  NAV,      NAV,      NAV,      NAV,      _______,  _______,            _______,
    _______,            KEYPAD,   KEYPAD,   KEYPAD,   KEYPAD,   _______,  _______,  _______,  _______,  _______,  _______,            _______,
    _______,  _______,  _______,                                _______,                                _______,  _______,  _______,  _______
};

const uint16_t functionColors[] = {
    _______,  BRIGHTN,  BRIGHTN,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,
    _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  DANGER,   _______,
    _______,  _______,  _______,  _______,  LED_ACT,  LED_ACT,  LED_ACT,  LED_ACT,  _______,  _______,  _______,  _______,            _______,
    _______,            LED_ACT,  LED_ACT,  LED_ACT,  LED_ACT,  LED_ACT,  LED_ACT,  LED_ACT,  LED_ACT,  LED_ACT,  LED_ACT,            _______,
    _______,  _______,  _______,                                _______,                                _______,  _______,  _______,  _______
};

void keyboard_post_init_user(void) {
}

RGB colorAt(uint8_t index, const uint16_t colors[]) {
    switch (colors[index]) {
        case NAV:         return COLOR_BLUE3;// (RGB){ .r = 137, .g = 207, .b = 240 };
        case M_NAV:       return COLOR_BLUE2;// (RGB){ .r = 115, .g = 150, .b = 255 };
        case M_VOL:       return COLOR_BLUE1;// (RGB){ .r = 0,   .g = 255, .b = 255 };
        case KEYPAD:      return (RGB){ .r = 255, .g = 69,  .b = 0   };
        case BRIGHTN:     return (RGB){ .r = 0,   .g = 255, .b = 255 };
        case LED_ACT:     return (RGB){ .r = 255, .g = 192, .b = 0   };
        case DANGER:      return (RGB){ .r = 255, .g = 0,   .b = 0   };
        case _______:     return (RGB){ .r = 0,   .g = 0,   .b = 0   };

        case WHITE:       return COLOR_WHITE;
        case RED:         return COLOR_RED;
        case ORANGE:      return COLOR_ORANGE;
        case BLUE1:       return COLOR_BLUE1;
        case BLUE2:       return COLOR_BLUE2;
        case BLUE3:       return COLOR_BLUE3;

        default:          return (RGB){ .r = 0,   .g = 0,   .b = 0   };
    }
}

void set_led_matrix(const uint16_t colors[]) {
    for (uint8_t i = 0; i < LED_MATRIX_COUNT; i++) {
        RGB rgb = colorAt(i, colors);
        uint8_t index = ledIndexes[i];
        is31fl3733_set_color(index, rgb.r, rgb.g, rgb.b);
    }
}

layer_state_t layer_state_set_user(layer_state_t state) {
    switch(biton32(state)) {
        case 0:
            backlight_timer_enable();
            break;

        case 1:
            backlight_timer_disable();
            set_led_matrix(utilsColors);
            break;

        case 2:
            backlight_timer_disable();
            set_led_matrix(functionColors);
            break;

        case 3:
            backlight_timer_disable();
            set_led_matrix(initColors);
            break;
    }

    return state;
}

void matrix_init_user(void) {
    backlight_timer_disable();
    set_led_matrix(initColors);
}

void matrix_scan_user(void) {
    //user matrix
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    return true;
}

uint16_t get_tapping_term(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case SLSH_LM:
            return 150;
        case CTL_TAB:
            return 140;
        default:
            return TAPPING_TERM;
    }
}

