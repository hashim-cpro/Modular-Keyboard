#pragma once

// Matrix configuration - matches info.json and layout
#define MATRIX_ROWS 5   
#define MATRIX_COLS 18  

#define CUSTOM_MATRIX

#define I2C_DRIVER I2CD1
#define I2C1_SDA_PIN GP4     
#define I2C1_SCL_PIN GP5     
#define I2C1_TIMINGR_PRESC 0U
#define I2C1_TIMINGR_SCLDEL 3U
#define I2C1_TIMINGR_SDADEL 1U
#define I2C1_TIMINGR_SCLH 3U
#define I2C1_TIMINGR_SCLL 9U


// Main keyboard: A pins to GND (A2=0, A1=0, A0=0) = 0x20
// Numpad: A pins to 3.3V (A2=1, A1=1, A0=1) = 0x27
#define PCF8575_MAIN_ADDR   0x20    // 64-key main matrix (8x8)
#define PCF8575_NUMPAD_ADDR 0x27    // 20-key numpad matrix (4x5)    

#define PCF8575_MAIN_INT_PIN   GP11   
#define PCF8575_NUMPAD_INT_PIN GP14   

// Main RGB configuration (first chain)
// RGB configuration
#define RGBLIGHT_LED_COUNT 82       // Total LEDs (64 main + 18 numpad)
#define WS2812_DI_PIN GP2           // Main RGB data pin (64 LEDs)

// Numpad RGB configuration (separate chain)
#define WS2812_NUMPAD_DI_PIN GP15   // Numpad RGB data pin (18 LEDs)

// RGB configuration
#define RGBLIGHT_EFFECT_RAINBOW_MOOD
#define RGBLIGHT_EFFECT_RAINBOW_SWIRL
#define RGBLIGHT_EFFECT_SNAKE
#define RGBLIGHT_EFFECT_KNIGHT
#define RGBLIGHT_EFFECT_CHRISTMAS
#define RGBLIGHT_EFFECT_STATIC_GRADIENT
#define RGBLIGHT_EFFECT_RGB_TEST
#define RGBLIGHT_EFFECT_ALTERNATING
#define RGBLIGHT_EFFECT_TWINKLE

// WS2812 driver configuration
#define WS2812_EXTERNAL_PULLUP      // If needed for signal integrity

// SK6812 MINI-E notes:
// - Compatible with WS2812 driver
// - Uses same protocol and timing
// - If LEDs don't work properly, try adjusting WS2812_TIMING

#define OLED_DISPLAY_128X64
#define OLED_TIMEOUT 60000

// Encoder Configuration  
#define ENCODER_RESOLUTION 4

// Debounce
#define DEBOUNCE 5
