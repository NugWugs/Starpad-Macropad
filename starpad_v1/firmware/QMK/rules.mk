# MCU / bootloader
MCU = RP2040
BOARD = GENERIC_RP_RP2040
BOOTLOADER = rp2040

# The 8-key matrix is a plain COL2ROW matrix (diodes conduct column -> row,
# which is exactly what QMK's stock scanner expects), so no custom matrix is
# needed -- it's configured data-driven in keyboard.json. The encoder's bare
# push-switch (GP0, no diode) is not a matrix key; it's read separately in
# the keymap's matrix_scan_user().

# Features
ENCODER_ENABLE = yes
EXTRAKEY_ENABLE = yes   # needed for KC_VOLU / KC_VOLD / KC_MUTE
OLED_ENABLE = yes
OLED_DRIVER = ssd1306
NKRO_ENABLE = yes
