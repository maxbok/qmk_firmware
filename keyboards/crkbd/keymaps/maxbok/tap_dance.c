#include QMK_KEYBOARD_H
#include "tap_dance.h"

typedef enum {
    TD_NONE,
    TD_UNKNOWN,
    TD_SINGLE_TAP,
    TD_SINGLE_HOLD,
    TD_DOUBLE_TAP,
    TD_DOUBLE_HOLD,
    TD_DOUBLE_SINGLE_TAP, // Send two single taps
    TD_TRIPLE_TAP,
    TD_TRIPLE_HOLD
} td_state_t;

typedef struct {
    bool is_press_action;
    td_state_t state;
} td_tap_t;

static td_tap_t abc_tap_state = {
    .is_press_action = true,
    .state = TD_NONE
};

td_state_t current_tap_dance(tap_dance_state_t *state) {
    if (state->count == 1) {
        if (state->interrupted || !state->pressed) return TD_SINGLE_TAP;
        // Key has not been interrupted, but the key is still held. Means you want to send a 'HOLD'.
        else return TD_SINGLE_HOLD;
    } else if (state->count == 2) {
        // TD_DOUBLE_SINGLE_TAP is to distinguish between typing "pepper", and actually wanting a double tap
        // action when hitting 'pp'. Suggested use case for this return value is when you want to send two
        // keystrokes of the key, and not the 'double tap' action/macro.
        if (state->interrupted) return TD_DOUBLE_SINGLE_TAP;
        else if (state->pressed) return TD_DOUBLE_HOLD;
        else return TD_DOUBLE_TAP;
    }
    // Assumes no one is trying to type the same letter three times (at least not quickly).
    // If your tap dance key is 'KC_W', and you want to type "www." quickly - then you will need to add
    // an exception here to return a 'TD_TRIPLE_SINGLE_TAP', and define that enum just like 'TD_DOUBLE_SINGLE_TAP'

    if (state->count == 3) {
        return TD_TRIPLE_TAP;
        // if (state->interrupted || !state->pressed) return TD_TRIPLE_TAP;
        // else return TD_TRIPLE_HOLD;
    } else return TD_UNKNOWN;
}

void abc_each(tap_dance_state_t *state, void *user_data) {
    if (state->count == 4) {
        reset_tap_dance(state);
    }
}

void abc_finished(tap_dance_state_t *state, void *user_data) {
    abc_tap_state.state = current_tap_dance(state);
    switch (abc_tap_state.state) {
        case TD_SINGLE_TAP:     register_code(KC_A);    break;
        case TD_SINGLE_HOLD:    register_code(KC_B);    break;
        case TD_DOUBLE_TAP:     register_code(KC_C);    break;
        case TD_DOUBLE_HOLD:    register_code(KC_D);    break;
        // Last case is for fast typing. Assuming your key is `f`:
        // For example, when typing the word `buffer`, and you want to make sure that you send `ff` and not `Esc`.
        // In order to type `ff` when typing fast, the next character will have to be hit within the `TAPPING_TERM`, which by default is 200ms.
        case TD_DOUBLE_SINGLE_TAP: tap_code(KC_E); register_code(KC_E); break;
        case TD_TRIPLE_TAP:        tap_code(KC_F); tap_code(KC_F); register_code(KC_F); break;
        default: break;
    }
}

void abc_reset(tap_dance_state_t *state, void *user_data) {
    switch (abc_tap_state.state) {
        case TD_SINGLE_TAP:         unregister_code(KC_A);  break;
        case TD_SINGLE_HOLD:        unregister_code(KC_B);  break;
        case TD_DOUBLE_TAP:         unregister_code(KC_C);  break;
        case TD_DOUBLE_HOLD:        unregister_code(KC_D);  break;
        case TD_DOUBLE_SINGLE_TAP:  unregister_code(KC_E);  break;
        case TD_TRIPLE_TAP:         unregister_code(KC_F);  break;

        default: break;
    }
    abc_tap_state.state = TD_NONE;
}

tap_dance_action_t tap_dance_actions[] = {
    [ABC] = ACTION_TAP_DANCE_FN_ADVANCED(abc_each, abc_finished, abc_reset)
};

