// !!! DO NOT ADD #pragma once !!! //

// Step 1.
// Declare custom effects using the RGB_MATRIX_EFFECT macro
// (note the lack of semicolon after the macro!)
RGB_MATRIX_EFFECT(REACTIVE_RXS)
RGB_MATRIX_EFFECT(REACTIVE_RXS_INVERSE)
RGB_MATRIX_EFFECT(MUTLIREACTIVE_RXS)
RGB_MATRIX_EFFECT(MUTLIREACTIVE_RXS_INVERSE)
RGB_MATRIX_EFFECT(SOLID_MULTISPLASH_RXS)
RGB_MATRIX_EFFECT(SOLID_MULTISPLASH_RXS_INVERSE)
RGB_MATRIX_EFFECT(MULTISPLASH_RXS)
RGB_MATRIX_EFFECT(MULTISPLASH_RXS_INVERSE)

// Step 2.
// Define effects inside the `RGB_MATRIX_CUSTOM_EFFECT_IMPLS` ifdef block
#ifdef RGB_MATRIX_CUSTOM_EFFECT_IMPLS

void set_key_colors(int offset, int sat) {
    uint8_t hue = rgb_matrix_config.hsv.h;
    HSV     hsv = {hue + offset, sat, 255};
    RGB     rgb = hsv_to_rgb(hsv);
    // modifier keysf
    int keys[] = {0, 13, 14, 15, 29, 30, 42, 43, 44, 55, 56, 57, 58, 59, 60, 62, 63, 64, 65, 66};
    for (unsigned int i = 0; i < 20; i = i + 1) {
        rgb_matrix_set_color(keys[i], rgb.r, rgb.g, rgb.b);
    }
}

static uint16_t reactive_effect(uint8_t dist, uint16_t tick) { return tick + dist * 5; }
static uint16_t splash_effect(uint8_t dist, uint16_t tick) { return tick - dist * 5; }

// static uint16_t cross_effect(int16_t dx, int16_t dy, uint8_t dist, uint16_t tick) {
//     uint16_t effect = tick + dist;
//     dx              = dx < 0 ? dx * -1 : dx;
//     dy              = dy < 0 ? dy * -1 : dy;
//     dx              = dx * 16 > 255 ? 255 : dx * 16;
//     dy              = dy * 16 > 255 ? 255 : dy * 16;
//     effect += dx > dy ? dy : dx;
//     return effect;
// }

static HSV RXS_math(HSV hsv, uint16_t effect, bool inverse, bool hue) {
    if (effect > 255) effect = 255;
    hsv.v = qadd8(scale8(128, hsv.v), 255 - (effect * 0.75));
    hsv.s = inverse ? qsub8(hsv.s, 255 - effect) : qadd8(scale8(0, hsv.s), 255 - effect);
    if (hue) hsv.h += effect + 1;
    return hsv;
}

static HSV REACTIVE_RXS_math(HSV hsv, int16_t dx, int16_t dy, uint8_t dist, uint16_t tick) {
    uint16_t effect = reactive_effect(dist, tick);
    return RXS_math(hsv, effect, false, false);
}

static HSV REACTIVE_RXS_INVERSE_math(HSV hsv, int16_t dx, int16_t dy, uint8_t dist, uint16_t tick) {
    uint16_t effect = reactive_effect(dist, tick);
    return RXS_math(hsv, effect, true, false);
}

static HSV MUTLIREACTIVE_RXS_math(HSV hsv, int16_t dx, int16_t dy, uint8_t dist, uint16_t tick) {
    uint16_t effect = reactive_effect(dist, tick);
    return RXS_math(hsv, effect, false, true);
}

static HSV MUTLIREACTIVE_RXS_INVERSE_math(HSV hsv, int16_t dx, int16_t dy, uint8_t dist, uint16_t tick) {
    uint16_t effect = reactive_effect(dist, tick);
    return RXS_math(hsv, effect, true, true);
}

static HSV SOLID_MULTISPLASH_RXS_math(HSV hsv, int16_t dx, int16_t dy, uint8_t dist, uint16_t tick) {
    uint16_t effect = splash_effect(dist, tick);
    return RXS_math(hsv, effect, false, false);
}

static HSV SOLID_MULTISPLASH_RXS_INVERSE_math(HSV hsv, int16_t dx, int16_t dy, uint8_t dist, uint16_t tick) {
    uint16_t effect = splash_effect(dist, tick);
    return RXS_math(hsv, effect, true, false);
}

static HSV MULTISPLASH_RXS_math(HSV hsv, int16_t dx, int16_t dy, uint8_t dist, uint16_t tick) {
    uint16_t effect = splash_effect(dist, tick);
    return RXS_math(hsv, effect, false, true);
}

static HSV MULTISPLASH_RXS_INVERSE_math(HSV hsv, int16_t dx, int16_t dy, uint8_t dist, uint16_t tick) {
    uint16_t effect = splash_effect(dist, tick);
    return RXS_math(hsv, effect, true, true);
}

bool REACTIVE_RXS(effect_params_t* params) {
    set_key_colors(-80, 255);
    return effect_runner_reactive_splash(0, params, &REACTIVE_RXS_math);
}
bool REACTIVE_RXS_INVERSE(effect_params_t* params) {
    set_key_colors(8, 255);
    return effect_runner_reactive_splash(0, params, &REACTIVE_RXS_INVERSE_math);
}
bool MUTLIREACTIVE_RXS(effect_params_t* params) {
    set_key_colors(-80, 255);
    return effect_runner_reactive_splash(0, params, &MUTLIREACTIVE_RXS_math);
}
bool MUTLIREACTIVE_RXS_INVERSE(effect_params_t* params) {
    set_key_colors(8, 255);
    return effect_runner_reactive_splash(0, params, &MUTLIREACTIVE_RXS_INVERSE_math);
}
bool SOLID_MULTISPLASH_RXS(effect_params_t* params) {
    set_key_colors(-80, 255);
    return effect_runner_reactive_splash(0, params, &SOLID_MULTISPLASH_RXS_math);
}
bool SOLID_MULTISPLASH_RXS_INVERSE(effect_params_t* params) {
    set_key_colors(8, 255);
    return effect_runner_reactive_splash(0, params, &SOLID_MULTISPLASH_RXS_INVERSE_math);
}
bool MULTISPLASH_RXS(effect_params_t* params) {
    set_key_colors(-80, 255);
    return effect_runner_reactive_splash(0, params, &MULTISPLASH_RXS_math);
}
bool MULTISPLASH_RXS_INVERSE(effect_params_t* params) {
    set_key_colors(8, 255);
    return effect_runner_reactive_splash(0, params, &MULTISPLASH_RXS_INVERSE_math);
}

#endif  // RGB_MATRIX_CUSTOM_EFFECT_IMPLS
