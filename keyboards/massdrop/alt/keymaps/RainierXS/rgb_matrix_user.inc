// !!! DO NOT ADD #pragma once !!! //

// Step 1.
// Declare custom effects using the RGB_MATRIX_EFFECT macro
// (note the lack of semicolon after the macro!)
RGB_MATRIX_EFFECT(REACTIVE_RXS)
RGB_MATRIX_EFFECT(REACTIVE_RXS_INVERSE)
RGB_MATRIX_EFFECT(SOLID_MULTISPLASH_RXS)
RGB_MATRIX_EFFECT(SOLID_MULTISPLASH_RXS_INVERSE)
RGB_MATRIX_EFFECT(MULTISPLASH_RXS)
RGB_MATRIX_EFFECT(MULTISPLASH_RXS_INVERSE)

// Step 2.
// Define effects inside the `RGB_MATRIX_CUSTOM_EFFECT_IMPLS` ifdef block
#ifdef RGB_MATRIX_CUSTOM_EFFECT_IMPLS

static HSV RXS_math(HSV hsv, uint16_t effect, bool inverse, bool hue) {
    if (effect > 255) effect = 255;
    hsv.v = qadd8(scale8(160, hsv.v), 255 - (effect*0.75));
    hsv.s = inverse ? qsub8(hsv.s, 255 - effect) : qadd8(scale8(0, hsv.s), 255 - effect);
    if (hue) hsv.h += effect + 1;
    return hsv;
}

static HSV REACTIVE_RXS_math(HSV hsv, int16_t dx, int16_t dy, uint8_t dist, uint16_t tick) {
    return RXS_math(hsv, tick + dist * 3, false, false);
}

static HSV REACTIVE_RXS_INVERSE_math(HSV hsv, int16_t dx, int16_t dy, uint8_t dist, uint16_t tick) {
    return RXS_math(hsv, tick + dist * 3, true, false);
}

static HSV SOLID_MULTISPLASH_RXS_math(HSV hsv, int16_t dx, int16_t dy, uint8_t dist, uint16_t tick) {
    return RXS_math(hsv, tick - dist * 3, false, false);
}

static HSV SOLID_MULTISPLASH_RXS_INVERSE_math(HSV hsv, int16_t dx, int16_t dy, uint8_t dist, uint16_t tick) {
    return RXS_math(hsv, tick - dist * 3, true, false);
}

static HSV MULTISPLASH_RXS_math(HSV hsv, int16_t dx, int16_t dy, uint8_t dist, uint16_t tick) {
    return RXS_math(hsv, tick - dist * 3, false, true);
}

static HSV MULTISPLASH_RXS_INVERSE_math(HSV hsv, int16_t dx, int16_t dy, uint8_t dist, uint16_t tick) {
    return RXS_math(hsv, tick - dist * 3, true, true);
}

bool REACTIVE_RXS(effect_params_t* params) { return effect_runner_reactive_splash(0, params, &REACTIVE_RXS_math); }
bool REACTIVE_RXS_INVERSE(effect_params_t* params) { return effect_runner_reactive_splash(0, params, &REACTIVE_RXS_INVERSE_math); }
bool SOLID_MULTISPLASH_RXS(effect_params_t* params) { return effect_runner_reactive_splash(0, params, &SOLID_MULTISPLASH_RXS_math); }
bool SOLID_MULTISPLASH_RXS_INVERSE(effect_params_t* params) { return effect_runner_reactive_splash(0, params, &SOLID_MULTISPLASH_RXS_INVERSE_math); }
bool MULTISPLASH_RXS(effect_params_t* params) { return effect_runner_reactive_splash(0, params, &MULTISPLASH_RXS_math); }
bool MULTISPLASH_RXS_INVERSE(effect_params_t* params) { return effect_runner_reactive_splash(0, params, &MULTISPLASH_RXS_INVERSE_math); }

#endif  // RGB_MATRIX_CUSTOM_EFFECT_IMPLS
