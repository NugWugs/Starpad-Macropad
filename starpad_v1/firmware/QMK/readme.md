# XIAO RP2040 Macropad (QMK)

Custom QMK keyboard for a Seeed XIAO RP2040 driving a 4x2 button matrix
(SW1-SW8), a rotary encoder + push-switch (SW12), and an SSD1306 0.91"
128x32 I2C OLED (U2).

## Pin map (from schematic, D-number -> GPIO)

| Signal   | XIAO pin | GPIO  |
|----------|----------|-------|
| Col1     | D0       | GP26  |
| Col2     | D1       | GP27  |
| Col3     | D2       | GP28  |
| Col4     | D3       | GP29  |
| Row1     | D8       | GP2   |
| Row2     | D7       | GP1   |
| RotA     | D9       | GP4   |
| RotB     | D10      | GP3   |
| RotEnc   | D6       | GP0   |
| SDA      | D4       | GP6   |
| SCL      | D5       | GP7   |

## Why a custom matrix.c

The schematic's diodes conduct **column -> row** (anode at the switch,
cathode toward the row net). QMK's stock `COL2ROW` scanner assumes the
opposite electrical polarity (idle-HIGH columns pulled briefly LOW,
rows pulled up and read LOW-for-pressed). To match your actual wiring,
`matrix.c` drives columns idle-LOW / active-HIGH and reads rows as
pulled-down / HIGH-for-pressed.

It also reads the encoder's push-switch (a plain switch-to-GND, no
diode) as a 9th key at matrix position `(row 2, col 0)`. Columns 1-3 of
row 2 don't physically exist and are left unmapped (`KC_NO` in the
keymap, though the default keymap only defines `KC_MUTE` at that one
real position).

**Double-check on the bench**: if the 8 main keys don't respond, or
respond only while held opposite of expected, the diode reading may be
backwards from what's on your schematic — flip the row read logic in
`matrix_scan_custom()` (swap `HIGH`/pull-down for `LOW`/pull-up) to
match.

## Build & flash

1. Drop this whole `xiao_rp2040_macropad` folder into
   `qmk_firmware/keyboards/`.
2. From the `qmk_firmware` root:
   ```
   qmk compile -kb xiao_rp2040_macropad -km default
   ```
3. Put the XIAO RP2040 into bootloader mode (double-tap the RESET
   button, or hold BOOTSEL while plugging in) — it will mount as a USB
   drive named `RPI-RP2`.
4. Copy the generated `.uf2` file (in
   `qmk_firmware/.build/`) onto that drive. The board reboots
   automatically running the new firmware.

## Customizing

- **Keymap**: edit `keymaps/default/keymap.c` — swap `KC_1`..`KC_8` for
  whatever keycodes/macros you actually want.
- **Encoder action**: `encoder_update_user()` in the same file currently
  does volume up/down; change it to anything else (media, custom
  layers, RGB, etc).
- **OLED content**: `oled_task_user()` currently just prints a static
  label — replace with layer indicators, WPM, encoder value, etc.
