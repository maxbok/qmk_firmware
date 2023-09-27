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

#define SLSH_LM LT(_NAV, KC_SLSH)
#define CTL_TAB CTL_T(KC_TAB)
#define SPC_SYM LT(_SYMBOLS, KC_SPC)
#define TG_TEST TG(_TEST)

#define PRV_TAB SCMD(KC_LCBR)
#define NXT_TAB SCMD(KC_RCBR)
#define WEB_PRV LCMD(KC_LBRC)
#define WEB_NXT LCMD(KC_RBRC)

enum layers {
    _QWERTY = 0,
    _SYMBOLS = 1,
    _NAV = 2,
    _FUNCTION = 3,
    _TEST = 4
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [_QWERTY] = LAYOUT_60_ansi(
    KC_ESC,   KC_1,     KC_2,     KC_3,     KC_4,     KC_5,     KC_6,     KC_7,     KC_8,     KC_9,     KC_0,     KC_MINS,  KC_EQL,   KC_BSPC, \
    KC_TAB,   KC_Q,     KC_W,     KC_E,     KC_R,     KC_T,     KC_Y,     KC_U,     KC_I,     KC_O,     KC_P,     KC_LBRC,  KC_RBRC,  KC_BSLS, \
    CTL_TAB,  KC_A,     KC_S,     KC_D,     KC_F,     KC_G,     KC_H,     KC_J,     KC_K,     KC_L,     KC_SCLN,  KC_QUOT,            KC_ENT,  \
    KC_LSFT,            KC_Z,     KC_X,     KC_C,     KC_V,     KC_B,     KC_N,     KC_M,     KC_COMM,  KC_DOT,   SLSH_LM,            KC_RSFT, \
    KC_LCTL,  KC_LALT,  KC_LCMD,                                SPC_SYM,                                KC_RCMD,  KC_RALT,  TG_TEST ,MO(_FUNCTION) \
  ),

  [_SYMBOLS] = LAYOUT_60_ansi(
    KC_GRV,   XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX, \
    _______,  KC_EXLM,  KC_AT,    KC_HASH,  KC_DLR,   KC_PERC,  KC_CIRC,  KC_AMPR,  KC_ASTR,  KC_LPRN,  KC_RPRN,  XXXXXXX,  XXXXXXX,  XXXXXXX, \
    _______,  KC_1,     KC_2,     KC_3,     KC_4,     KC_5,     KC_6,     KC_7,     KC_8,     KC_9,     KC_0,     XXXXXXX,            _______, \
    _______,            XXXXXXX,  KC_SCLN,  KC_COLN,  KC_MINS,  KC_EQL,   KC_LCBR,  KC_LBRC,  KC_RBRC,  KC_RCBR,  XXXXXXX,            _______, \
    _______,  _______,  _______,                                XXXXXXX,                                _______,  _______,  _______,  _______  \
  ),

  [_NAV] = LAYOUT_60_ansi(
    KC_GRV,   XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  KC_VOLD,  KC_VOLU,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX, \
    _______,  KC_BRMD,  KC_BRMU,  XXXXXXX,  KC_VOLD,  KC_VOLU,  XXXXXXX,  KC_MPRV,  KC_MPLY,  KC_MNXT,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX, \
    _______,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  KC_LEFT,  KC_DOWN,  KC_UP,    KC_RGHT,  XXXXXXX,  XXXXXXX,            _______, \
    _______,            XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  WEB_PRV,  PRV_TAB,  NXT_TAB,  WEB_NXT,  XXXXXXX,            _______, \
    _______,  _______,  _______,                                XXXXXXX,                                _______,  _______,  _______,  _______  \
  ),

  [_FUNCTION] = LAYOUT_60_ansi(
    XXXXXXX,  KC_BRMD,  KC_BRMU,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  KC_DEL,  \
    XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  QK_BOOT,  XXXXXXX, \
    XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  S1_DEC,   S1_INC,   S2_DEC,   S2_INC,   XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,            XXXXXXX, \
    XXXXXXX,            EF_DEC,   EF_INC,   H1_DEC,   H1_INC,   H2_DEC,   H2_INC,   BR_DEC,   BR_INC,   ES_DEC,   ES_INC,             XXXXXXX, \
    XXXXXXX,  XXXXXXX,  XXXXXXX,                                XXXXXXX,                                XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX  \
  ),

  [_TEST] = LAYOUT_60_ansi(
    XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX, \
    XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX, \
    XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,            XXXXXXX, \
    XXXXXXX,            XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,            XXXXXXX, \
    XXXXXXX,  XXXXXXX,  XXXXXXX,                                XXXXXXX,                                XXXXXXX,  XXXXXXX,  TG_TEST,  XXXXXXX  \
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
#define NUM 40
#define WEB 50
#define TAB 60
#define BRIGHTN 100
#define LED_ACT 110
#define DANGER 120

#define WHITE    200
#define RED      210
#define ORANGE   220
#define DARKORG  225
#define BLUE1    230
#define BLUE2    231
#define BLUE3    232

#define COLOR_WHITE         (RGB){ .r = 200, .g = 255, .b = 255 }
#define COLOR_RED           (RGB){ .r = 255, .g = 0,   .b = 0   }
#define COLOR_ORANGE        (RGB){ .r = 255, .g = 192, .b = 0   }
#define COLOR_DARK_ORANGE   (RGB){ .r = 255, .g = 80,  .b = 0   }
#define COLOR_BLUE1         (RGB){ .r = 0,   .g = 0,   .b = 255 }
#define COLOR_BLUE2         (RGB){ .r = 15,  .g = 72,  .b = 255 }
#define COLOR_BLUE3         (RGB){ .r = 30,  .g = 144, .b = 255 }

const uint16_t initColors[] = {
    _______,  _______,  _______,  _______,  _______,  BLUE1,    BLUE1,    BLUE1,    BLUE1,    BLUE1,    BLUE1,    BLUE1,    BLUE1,    BLUE1,  
    _______,  _______,  _______,  _______,  BLUE2,    BLUE2,    BLUE2,    BLUE2,    BLUE2,    BLUE2,    BLUE2,    BLUE2,    BLUE2,    BLUE2,    
    _______,  _______,  _______,  BLUE3,    BLUE3,    BLUE3,    BLUE3,    BLUE3,    BLUE3,    BLUE3,    BLUE3,    BLUE3,              BLUE3,
    _______,            _______,  ORANGE,   ORANGE,   ORANGE,   ORANGE,   ORANGE,   ORANGE,   ORANGE,   ORANGE,   ORANGE,             ORANGE, 
    _______,  _______,  RED,                                    RED,                                    RED,      RED,      RED,      RED
};

const uint16_t symbolsColors[] = {
    BLUE1,    _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,
    _______,  BLUE2,    BLUE2,    BLUE2,    BLUE2,    BLUE2,    BLUE2,    BLUE2,    BLUE2,    BLUE2,    BLUE2,    _______,  _______,  _______,
    _______,  BLUE3,    BLUE3,    BLUE3,    BLUE3,    BLUE3,    BLUE3,    BLUE3,    BLUE3,    BLUE3,    BLUE3,    _______,            _______,
    _______,            _______,  DARKORG,  DARKORG,  DARKORG,  DARKORG,  ORANGE,   ORANGE,   ORANGE,   ORANGE,   _______,            _______,
    _______,  _______,  _______,                                _______,                                _______,  _______,  _______,  _______
};

const uint16_t navColors[] = {
    _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  M_VOL,    M_VOL,    _______,  _______,  _______,  _______,
    _______,  BRIGHTN,  BRIGHTN,  _______,  M_VOL,    M_VOL,    _______,  M_NAV,    M_NAV,    M_NAV,    _______,  _______,  _______,  _______,
    _______,  _______,  _______,  _______,  _______,  _______,  NAV,      NAV,      NAV,      NAV,      _______,  _______,            _______,
    _______,            _______,  _______,  _______,  _______,  _______,  WEB,      TAB,      TAB,      WEB,      _______,            _______,
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
        case NUM:         return (RGB){ .r = 255, .g = 69,  .b = 0   };
        case WEB:         return COLOR_ORANGE;
        case TAB:         return COLOR_DARK_ORANGE;
        case BRIGHTN:     return (RGB){ .r = 0,   .g = 255, .b = 255 };
        case LED_ACT:     return (RGB){ .r = 255, .g = 192, .b = 0   };
        case DANGER:      return (RGB){ .r = 255, .g = 0,   .b = 0   };
        case _______:     return (RGB){ .r = 0,   .g = 0,   .b = 0   };

        case WHITE:       return COLOR_WHITE;
        case RED:         return COLOR_RED;
        case ORANGE:      return COLOR_ORANGE;
        case DARKORG:     return COLOR_DARK_ORANGE;
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
        case _QWERTY:
            backlight_timer_enable();
            break;

        case _SYMBOLS:
            backlight_timer_disable();
            set_led_matrix(symbolsColors);
            break;

        case _NAV:
            backlight_timer_disable();
            set_led_matrix(navColors);
            break;

        case _FUNCTION:
            backlight_timer_disable();
            set_led_matrix(functionColors);
            break;

        case _TEST:
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
        case SPC_SYM:
            return 250;
        default:
            return TAPPING_TERM;
    }
}

