
MCU = RP2040
BOOTLOADER = rp2040

EXTRAKEY_ENABLE = yes       
MOUSEKEY_ENABLE = yes       
NKRO_ENABLE = yes          # USB N-Key Rollover
RGBLIGHT_ENABLE = yes      
ENCODER_ENABLE = yes       
OLED_ENABLE = yes         

# Custom matrix for I2C expanders
CUSTOM_MATRIX = lite

I2C_DRIVER_REQUIRED = yes

AUDIO_ENABLE = no


CONSOLE_ENABLE = no

COMMAND_ENABLE = no

SLEEP_LED_ENABLE = no

BOOTMAGIC_ENABLE = yes

# VIA support (for easy keymap editing)
VIA_ENABLE = yes
