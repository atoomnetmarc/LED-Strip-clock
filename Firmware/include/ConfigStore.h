/**
 * @file ConfigStore.h
 * @brief JSON configuration store on LittleFS
 *
 * @copyright Marc Ketel
 * SPDX-License-Identifier: Apache-2.0
 */

#pragma once

#include <Arduino.h>

namespace configstore {
    // Display brightness in percent (0-100). The /OE shift-register pin is
    // active-low, so a higher percentage means a lower PWM duty cycle.
    // Clamp a brightness value to the valid range. The minimum is 1% so the
    // display never goes fully dark via configuration.
    inline uint8_t clampBrightness(long percent) {
        if (percent < 1) {
            return 1;
        }
        if (percent > 100) {
            return 100;
        }
        return static_cast<uint8_t>(percent);
    }

    inline uint16_t pwmFromBrightness(uint8_t percent) {
        if (percent > 100) {
            percent = 100;
        }
        return 1023 - static_cast<uint16_t>(percent) * 1023 / 100;
    }

    struct Config {
        uint8_t brightness; // percent 0-100
        char ssid[33];
        char wifiPassword[65];
        char ntpServer[65];
        char timezone[65];
        char hostname[33];
        char adminPassword[65];
    };

    extern Config config;

    // Mount LittleFS and load /config.json; falls back to defaults when the
    // file is absent or invalid, and persists the defaults in that case.
    void begin();

    // Atomically persist the current config to /config.json
    // (write to /config.json.tmp, then rename). Returns true on success.
    bool save();

    // True when no valid stored config exists (defaults in use).
    bool usingDefaults();
}
