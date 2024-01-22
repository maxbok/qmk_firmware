#pragma once

#include "maxbok.h"

void rgb_keyboard_init(void);

typedef uint16_t COLOR_SYMBOL;

RGB symbol_to_rgb(COLOR_SYMBOL symbol);
const uint16_t color_symbols[4][MATRIX_ROWS][MATRIX_COLS];

