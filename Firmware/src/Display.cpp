/**
 * @file Display.cpp
 * @brief 7-segment display driver implementation
 *
 * @copyright Marc Ketel
 * SPDX-License-Identifier: Apache-2.0
 */

#include <Arduino.h>

#include "Display.h"

#include <time.h>

#include "Pins.h"

namespace display {

    // Segment bits: a=0, b=1, c=2, d=3, e=4, f=5, g=6.
    // Digits match the original digits[] table; letters are remapped from the
    // n-teller-xl-diy font to this bit order.
    const uint8_t font[96] = {
        // Index = ASCII code. Unmapped characters render blank.
        // Segment bits: a=0, b=1, c=2, d=3, e=4, f=5, g=6.
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0, // 0x00..0x0F
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0, // 0x10..0x1F
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0, // 0x20..0x2F
        0b0111111,
        0b0000110,
        0b1011011,
        0b1001111,
        0b1100110,
        0b1101101,
        0b1111101,
        0b0000111,
        0b1111111,
        0b1101111,
        0,
        0,
        0,
        0,
        0,
        0, // 0x30..0x3F
        0,
        0b1110111,
        0,
        0,
        0,
        0b1111001,
        0,
        0,
        0b1110110,
        0,
        0,
        0,
        0,
        0,
        0,
        0, // 0x40..0x4F
        0b1110011,
        0,
        0,
        0b1101101,
        0,
        0b0111110,
        0b0111110,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0b0001000, // 0x50..0x5F
    };

    void write(const uint8_t *patterns) {
        // The first pattern shifted ends up farthest in the chain. The original
        // code shifted the seconds first and the hour-tens last, so index 0
        // (leftmost) must be shifted last.
        for (uint8_t i = kDigitCount; i > 0; i--) {
            shiftOut(PIN_SHIFT_DATA, PIN_SHIFT_CLOCK, MSBFIRST, patterns[i - 1]);
        }
    }

    void timePatterns(uint8_t *patterns, const struct tm &timeInfo) {
        patterns[0] = font['0' + (timeInfo.tm_hour / 10) % 10];
        patterns[1] = font['0' + timeInfo.tm_hour % 10];
        patterns[2] = font['0' + (timeInfo.tm_min / 10) % 10];
        patterns[3] = font['0' + timeInfo.tm_min % 10];
        patterns[4] = font['0' + (timeInfo.tm_sec / 10) % 10];
        patterns[5] = font['0' + timeInfo.tm_sec % 10];
    }

    void textPatterns(uint8_t *patterns, const char *text) {
        for (uint8_t i = 0; i < kDigitCount; i++) {
            patterns[i] = 0; // blank
        }
        for (uint8_t i = 0; i < kDigitCount && text[i] != '\0'; i++) {
            uint8_t c = static_cast<uint8_t>(text[i]);
            if (c < sizeof(font)) {
                patterns[i] = font[c];
            }
        }
    }

} // namespace display
