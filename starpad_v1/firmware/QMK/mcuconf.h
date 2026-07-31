// The RP2040 board defaults leave every I2C peripheral disabled, so the
// ChibiOS driver object I2CD1 (which binds to the RP2040 I2C1 hardware,
// i.e. the SDA=GP6 / SCL=GP7 pair the OLED is wired to) never gets
// compiled in. Enable I2C1 here so config.h's `#define I2C_DRIVER I2CD1`
// resolves. I2C0 stays off; we don't use it.
#pragma once

#include_next <mcuconf.h>

#undef RP_I2C_USE_I2C0
#define RP_I2C_USE_I2C0 FALSE

#undef RP_I2C_USE_I2C1
#define RP_I2C_USE_I2C1 TRUE
