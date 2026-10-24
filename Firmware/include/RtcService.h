/**
 * @file RtcService.h
 * @brief DS3231 RTC support: boot time seeding and NTP write-back
 *
 * The DS3231MZ (I2C address 0x68, INT pin on D6) is the fallback time
 * source. At boot the system clock is seeded from the RTC; on every NTP
 * sync the (more accurate) system time is written back to the RTC.
 *
 * @copyright Marc Ketel
 * SPDX-License-Identifier: Apache-2.0
 */

#pragma once

#include <Arduino.h>

namespace rtc {
    // Probe the RTC and seed the system clock from it. Call after Wire.begin().
    void begin();

    // True when the RTC answered at 0x68 during begin().
    bool present();

    // Read the RTC time into out (UTC). Returns false when absent/read error.
    bool getTime(struct tm &out);

    // Difference in seconds between RTC time and the system clock (RTC - system).
    // Only meaningful when present().
    int32_t driftSeconds();

    // DS3231 on-chip crystal temperature in degrees Celsius.
    float temperature();

    // Write the current system time to the RTC (called on NTP sync).
    // Returns false when the RTC is absent or the write failed.
    bool syncFromSystem();
}
