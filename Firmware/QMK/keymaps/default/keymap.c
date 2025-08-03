// Layer 0: Base layer
// Layer 1: Function layer
// Layer 2: RGB/System layer

#include QMK_KEYBOARD_H

static bool numpad_rgb_enabled = true;
static uint8_t numpad_rgb_mode = 0;


typedef enum {
    NUMPAD_RGB_OFF = 0,
    NUMPAD_RGB_SOLID,
    NUMPAD_RGB_BREATHING,
    NUMPAD_RGB_RAINBOW,
    NUMPAD_RGB_MODES_COUNT
} numpad_rgb_mode_t;

enum custom_keycodes {
    RGB_TOG_MAIN = SAFE_RANGE,
    RGB_TOG_NUMPAD,
    RGB_MOD_NUMPAD,    
    RGB_HUI_NUMPAD,    
    RGB_HUD_NUMPAD,    
    RGB_VAI_NUMPAD,    
    RGB_VAD_NUMPAD,    
    OLED_TOG
};

enum layer_names {
    _BASE,
    _FN,
    _RGB
};

static void numpad_rgb_update(void) {
    // Simplified RGB function using standard QMK RGB
    if (!numpad_rgb_enabled) {
        rgblight_disable();
    } else {
        rgblight_enable();
        switch (numpad_rgb_mode) {
            case NUMPAD_RGB_SOLID:
                rgblight_mode(RGBLIGHT_MODE_STATIC_LIGHT);
                break;
                
            case NUMPAD_RGB_BREATHING:
                rgblight_mode(RGBLIGHT_MODE_BREATHING);
                break;
                
            case NUMPAD_RGB_RAINBOW:
                rgblight_mode(RGBLIGHT_MODE_RAINBOW_MOOD);
                break;
                
            default:
                rgblight_disable();
                break;
        }
    }
}

// Toggle numpad RGB
static void numpad_rgb_toggle(void) {
    numpad_rgb_enabled = !numpad_rgb_enabled;
    numpad_rgb_update();
}

// Cycle numpad RGB mode
static void numpad_rgb_mode_step(void) {
    numpad_rgb_mode = (numpad_rgb_mode + 1) % NUMPAD_RGB_MODES_COUNT;
    numpad_rgb_update();
}
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

    [_BASE] = LAYOUT(
        // Main keyboard (60% layout)
        KC_ESC,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS, KC_EQL,  KC_BSPC,
        KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_LBRC, KC_RBRC, KC_BSLS,
        KC_CAPS, KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT, KC_ENT,
        KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_RSFT, KC_UP,
        KC_LCTL, KC_LGUI, KC_LALT, KC_SPC,  KC_RALT, MO(_FN), KC_LEFT, KC_DOWN, KC_RGHT, KC_HOME, KC_END,
        
        // Numpad
        KC_NUM,  KC_PSLS, KC_PAST, KC_PMNS,
        KC_P7,   KC_P8,   KC_P9,   KC_PPLS,
        KC_P4,   KC_P5,   KC_P6,
        KC_P1,   KC_P2,   KC_P3,   KC_PENT,
        KC_P0,   KC_PDOT, KC_DEL
    ),

    [_FN] = LAYOUT(
        // Main keyboard function layer
        KC_GRV,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  KC_DEL,
        KC_TRNS, KC_TRNS, KC_UP,   KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_INS,  KC_TRNS, KC_PSCR, KC_SCRL, KC_PAUS, KC_TRNS,
        KC_TRNS, KC_LEFT, KC_DOWN, KC_RGHT, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_HOME, KC_PGUP, KC_TRNS, KC_TRNS, KC_TRNS,
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_END,  KC_PGDN, KC_TRNS, KC_TRNS, KC_VOLU,
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, MO(_RGB), KC_MPRV, KC_VOLD, KC_MNXT, KC_MPLY, KC_MUTE,
        
        // Numpad function layer
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
        KC_HOME, KC_UP,   KC_PGUP, KC_TRNS,
        KC_LEFT, KC_TRNS, KC_RGHT,
        KC_END,  KC_DOWN, KC_PGDN, KC_TRNS,
        KC_INS,  KC_DEL,  KC_TRNS
    ),

    [_RGB] = LAYOUT(
        // RGB and system controls
        QK_BOOT, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
        KC_TRNS, RGB_TOG, RGB_MOD, RGB_HUI, RGB_HUD, RGB_SAI, RGB_SAD, RGB_VAI, RGB_VAD, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
        KC_TRNS, RGB_TOG_MAIN, RGB_TOG_NUMPAD, RGB_MOD_NUMPAD, RGB_HUI_NUMPAD, RGB_HUD_NUMPAD, RGB_VAI_NUMPAD, RGB_VAD_NUMPAD, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
        
        // Numpad RGB layer
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
        KC_TRNS, KC_TRNS, KC_TRNS,
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
        KC_TRNS, KC_TRNS, KC_TRNS
    )
};

// Encoder mapping
#if defined(ENCODER_MAP_ENABLE)
const uint16_t PROGMEM encoder_map[][NUM_ENCODERS][2] = {
    [_BASE] = { ENCODER_CCW_CW(KC_VOLD, KC_VOLU) },
    [_FN]   = { ENCODER_CCW_CW(KC_MPRV, KC_MNXT) },
    [_RGB]  = { ENCODER_CCW_CW(RGB_VAD, RGB_VAI) },
};
#endif

// OLED display code
#ifdef OLED_ENABLE
bool oled_task_user(void) {
    // Host keyboard layer status
    oled_write_P(PSTR("Layer: "), false);
    switch (get_highest_layer(layer_state)) {
        case _BASE:
            oled_write_P(PSTR("Base\n"), false);
            break;
        case _FN:
            oled_write_P(PSTR("Function\n"), false);
            break;
        case _RGB:
            oled_write_P(PSTR("RGB/System\n"), false);
            break;
        default:
            oled_write_P(PSTR("Undefined\n"), false);
    }

    // Host keyboard LED status
    led_t led_state = host_keyboard_led_state();
    oled_write_P(led_state.num_lock ? PSTR("NUM ") : PSTR("    "), false);
    oled_write_P(led_state.caps_lock ? PSTR("CAP ") : PSTR("    "), false);
    oled_write_P(led_state.scroll_lock ? PSTR("SCR ") : PSTR("    "), false);

    return false;
}
#endif

// Initialize numpad RGB on startup
void keyboard_post_init_user(void) {
    // Initialize numpad RGB to solid color
    numpad_rgb_mode = NUMPAD_RGB_SOLID;
    numpad_rgb_update();
}

// Housekeeping task for numpad RGB animations
void housekeeping_task_user(void) {
    // Update numpad RGB if enabled and in animated mode
    if (numpad_rgb_enabled && (numpad_rgb_mode == NUMPAD_RGB_BREATHING || numpad_rgb_mode == NUMPAD_RGB_RAINBOW)) {
        static uint32_t last_update = 0;
        if (timer_elapsed32(last_update) > 50) { // Update every 50ms
            numpad_rgb_update();
            last_update = timer_read32();
        }
    }
}

// Custom keycode handling
bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case RGB_TOG_MAIN:
            if (record->event.pressed) {
                // Toggle RGB for main keyboard (64 LEDs on GP2)
                rgblight_toggle();
            }
            return false;
        case RGB_TOG_NUMPAD:
            if (record->event.pressed) {
                // Toggle RGB for numpad (18 LEDs on GP15)
                numpad_rgb_toggle();
            }
            return false;
        case RGB_MOD_NUMPAD:
            if (record->event.pressed) {
                // Cycle numpad RGB modes
                numpad_rgb_mode_step();
            }
            return false;
        case RGB_HUI_NUMPAD:
            if (record->event.pressed) {
                rgblight_increase_hue();
            }
            return false;
        case RGB_HUD_NUMPAD:
            if (record->event.pressed) {
                rgblight_decrease_hue();
            }
            return false;
        case RGB_VAI_NUMPAD:
            if (record->event.pressed) {
                rgblight_increase_val();
            }
            return false;
        case RGB_VAD_NUMPAD:
            if (record->event.pressed) {
                rgblight_decrease_val();
            }
            return false;
        case OLED_TOG:
            if (record->event.pressed) {
                // Toggle OLED display
                oled_clear();
                // TODO: Implement OLED on/off toggle
            }
            return false;
    }
    return true;
}
