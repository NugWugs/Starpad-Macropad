#include QMK_KEYBOARD_H

// The encoder's push-switch (SW12) is a bare switch to GND on GP0 with no
// diode, so it can't live in the key matrix. We read it directly here.
#define ENC_SW_PIN GP0

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [0] = LAYOUT(
        KC_1,    KC_2,    KC_3,    KC_4,
        KC_5,    KC_6,    KC_7,    KC_8
    ),
};

void keyboard_pre_init_user(void) {
    // Switch-to-GND button: enable the internal pull-up so it idles HIGH
    // and reads LOW when pressed.
    gpio_set_pin_input_high(ENC_SW_PIN);
}

// Read the encoder push-switch every scan and tap KC_MUTE on each press.
// The matrix debounce.c doesn't cover this pin, so we do a small time-guard
// debounce ourselves (DEBOUNCE ms, same window the matrix uses).
void matrix_scan_user(void) {
    static bool     pressed     = false;
    static uint16_t last_change = 0;

    bool now = !gpio_read_pin(ENC_SW_PIN); // active-low: LOW = pressed
    if (now != pressed && timer_elapsed(last_change) > DEBOUNCE) {
        pressed     = now;
        last_change = timer_read();
        if (pressed) {
            tap_code(KC_MUTE);
        }
    }
}

bool encoder_update_user(uint8_t index, bool clockwise) {
    if (index == 0) {
        if (clockwise) {
            tap_code(KC_VOLU);
        } else {
            tap_code(KC_VOLD);
        }
    }
    return false;
}

#ifdef OLED_ENABLE
bool oled_task_user(void) {
    oled_write_P(PSTR("Macropad\n"), false);
    oled_write_P(PSTR("8 keys + enc\n"), false);
    return false;
}
#endif
