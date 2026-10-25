/**
 * @file Display.h
 * @brief 7-segment display driver with font table and message modes
 *
 * Segment bit order: a=0, b=1, c=2, d=3, e=4, f=5, g=6.
 *
 * @copyright Marc Ketel
 * SPDX-License-Identifier: Apache-2.0
 */

#pragma once

#include <stdint.h>
#include <time.h>

namespace display {

    // 7-segment patterns, indexed by ASCII value.
    // Segment bits: a=0, b=1, c=2, d=3, e=4, f=5, g=6.
    // Letters remapped from the n-teller-xl-diy font.
    extern const uint8_t font[96];

    // Number of display digits.
    constexpr uint8_t kDigitCount = 6;

    /**
     * @brief Push 6 segment patterns to the shift registers.
     *
     * @param patterns Array of kDigitCount segment patterns, index 0 = leftmost.
     */
    void write(const uint8_t *patterns);

    /**
     * @brief Render the current time (HHMMSS) to a pattern buffer.
     *
     * @param patterns Output buffer of kDigitCount entries.
     * @param timeInfo Broken-down local time.
     */
    void timePatterns(uint8_t *patterns, const struct tm &timeInfo);

    /**
     * @brief Render a left-aligned 4-character message to a pattern buffer.
     * Remaining digits are blank. Unknown characters render blank.
     *
     * @param patterns Output buffer of kDigitCount entries.
     * @param text NUL-terminated message, up to 4 visible characters.
     */
    void textPatterns(uint8_t *patterns, const char *text);

} // namespace display
