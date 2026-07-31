#pragma once

// --- OLED (U2, ER-OLED0.91-1, SSD1306 128x32) ---
// SDA = D4 = GP6, SCL = D5 = GP7 -> this pair lives on RP2040's I2C1 block
#define I2C_DRIVER I2CD1
#define I2C1_SDA_PIN GP6
#define I2C1_SCL_PIN GP7
#define OLED_DISPLAY_128X32

// Standard matrix debounce. Also reused as the settle window for the
// encoder push-switch, which is read outside the matrix in matrix_scan_user().
#define DEBOUNCE 5
