#ifdef RGB_MATRIX_CUSTOM_EFFECT_IMPLS

uint32_t timer_init_value;

void WAKEUP_init(effect_params_t* params) {
    rgb_matrix_set_speed_noeeprom(100);
    timer_init_value = g_rgb_timer;
}

HSV hsv_for_timer(uint16_t timer) {
    switch (timer) {
        case 0 ... 40:
            return (HSV) { HSV_GREEN };
        case 41 ... 80:
            return (HSV) { HSV_ORANGE };
        default:
            return (HSV) { HSV_RED };
    }
}

bool WAKEUP_run(effect_params_t* params) {
    uint16_t timer = scale16by8(g_rgb_timer - timer_init_value, rgb_matrix_config.speed / 8);

    if (timer >= 120) {
        rgb_matrix_mode_noeeprom(RGB_MATRIX_CUSTOM_QWERTY);
        return false;
    }

    HSV hsv = hsv_for_timer(timer); 

    RGB_MATRIX_USE_LIMITS(led_min, led_max);
    for (uint8_t i = led_min; i < led_max; i++) {
        uint16_t time = scale16by8(g_rgb_timer + (i * 315), rgb_matrix_config.speed / 8);
        hsv.v         = scale8(abs8(sin8(time) - 128) * 2, hsv.v);
        RGB rgb       = rgb_matrix_hsv_to_rgb(hsv);
        RGB_MATRIX_TEST_LED_FLAGS();
        rgb_matrix_set_color(i, rgb.r, rgb.g, rgb.b);
    }

    return rgb_matrix_check_finished_leds(led_max);
}

bool WAKEUP(effect_params_t* params) {
    if (params->init) {
        WAKEUP_init(params);
    }
    return WAKEUP_run(params);
}

#endif
