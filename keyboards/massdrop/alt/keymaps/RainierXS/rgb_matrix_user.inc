// !!! DO NOT ADD #pragma once !!! //

// Step 1.
// Declare custom effects using the RGB_MATRIX_EFFECT macro
// (note the lack of semicolon after the macro!)
RGB_MATRIX_EFFECT(REACTIVE_SPLASH_RXS)
RGB_MATRIX_EFFECT(REACTIVE_SPLASH_RXS_INVERSE)

// Step 2.
// Define effects inside the `RGB_MATRIX_CUSTOM_EFFECT_IMPLS` ifdef block
#ifdef RGB_MATRIX_CUSTOM_EFFECT_IMPLS

static HSV REACTIVE_SPLASH_RXS_math(HSV hsv, int16_t dx, int16_t dy, uint8_t dist, uint16_t tick) {
    uint16_t effect = tick + dist * 3;
    hsv.s           = scale8(0, hsv.s);
    hsv.v           = scale8(127, hsv.v);
    if (effect > 255) effect = 255;
    if (effect) hsv.v = qadd8(hsv.v, 255 - (effect*0.75));
    if (effect) hsv.s = qadd8(hsv.s, 255 - effect);
    return hsv;
}

static HSV REACTIVE_SPLASH_RXS_INVERSE_math(HSV hsv, int16_t dx, int16_t dy, uint8_t dist, uint16_t tick) {
    uint16_t effect = tick + dist * 3;
    hsv.s           = scale8(255, hsv.s);
    hsv.v           = scale8(127, hsv.v);
    if (effect > 255) effect = 255;
    if (effect) hsv.v = qadd8(hsv.v, 255 - (effect*0.75));
    if (effect) hsv.s = qsub8(hsv.s, 255 - effect);
    return hsv;
}

bool REACTIVE_SPLASH_RXS(effect_params_t* params) { return effect_runner_reactive_splash(0, params, &REACTIVE_SPLASH_RXS_math); }
bool REACTIVE_SPLASH_RXS_INVERSE(effect_params_t* params) { return effect_runner_reactive_splash(0, params, &REACTIVE_SPLASH_RXS_INVERSE_math); }

#endif  // RGB_MATRIX_CUSTOM_EFFECT_IMPLS
