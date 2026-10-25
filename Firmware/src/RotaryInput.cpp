/**
 * @file RotaryInput.cpp
 * @brief Quadrature decoder + debounced switch for a rotary encoder behind an MCP23008.
 *
 * @copyright Marc Ketel
 * SPDX-License-Identifier: Apache-2.0
 */

#include <Arduino.h>

#include "RotaryInput.h"

namespace rotaryinput {

    namespace {

        // Quadrature transition table. Index = (prevAB << 2) | newAB, where AB is a
        // 2-bit value (bit0 = A, bit1 = B). Valid transitions yield +1 (CW) or -1
        // (CCW); invalid jumps (both bits changed, i.e. contact bounce or a missed
        // edge) yield 0 so they are ignored.
        //      newAB: 00   01   10   11
        const int8_t kQuadrature[16] = {
            // prevAB = 00
            0, -1, +1, 0,
            // prevAB = 01
            +1, 0, 0, -1,
            // prevAB = 10
            -1, 0, 0, +1,
            // prevAB = 11
            0, +1, -1, 0};

        constexpr int8_t kEdgesPerDetent = 4;
        constexpr uint32_t kDebounceMs = 30;
        constexpr uint32_t kLongPressMs = 600;

        uint8_t g_bitA = 0;
        uint8_t g_bitB = 0;
        uint8_t g_bitSw = 0;
        bool g_activeLowSw = true;

        uint8_t g_prevAB = 0;
        int8_t g_accum = 0;

        bool g_switchRaw = false;     // debounced state, true = pressed
        bool g_switchLastRaw = false; // previous raw sample
        uint32_t g_switchChangedMs = 0;
        uint32_t g_switchPressedMs = 0;
        bool g_longPressFired = false;

        inline bool readBit(uint8_t value, uint8_t bit) {
            return (value >> bit) & 1;
        }

    } // namespace

    void begin(uint8_t portMaskBitsA, uint8_t portMaskBitsB, uint8_t portMaskBitsSw,
               bool activeLowSwitch) {
        g_bitA = portMaskBitsA;
        g_bitB = portMaskBitsB;
        g_bitSw = portMaskBitsSw;
        g_activeLowSw = activeLowSwitch;
        g_prevAB = 0;
        g_accum = 0;
        g_switchRaw = false;
        g_switchLastRaw = false;
        g_longPressFired = false;
    }

    Event update(uint8_t portValue) {
        // --- Quadrature decoding ---
        uint8_t ab = (readBit(portValue, g_bitA) ? 1 : 0) |
                     (readBit(portValue, g_bitB) ? 2 : 0);

        Event event = Event::None;

        if (ab != g_prevAB) {
            g_accum += kQuadrature[(g_prevAB << 2) | ab];
            g_prevAB = ab;

            if (g_accum >= kEdgesPerDetent) {
                g_accum = 0;
                event = Event::Cw;
            } else if (g_accum <= -kEdgesPerDetent) {
                g_accum = 0;
                event = Event::Ccw;
            }
        }

        // --- Switch debouncing ---
        bool raw = readBit(portValue, g_bitSw);
        if (g_activeLowSw) {
            raw = !raw; // normalize: true = pressed
        }

        uint32_t now = millis();

        if (raw != g_switchLastRaw) {
            g_switchLastRaw = raw;
            g_switchChangedMs = now;
        } else if (raw != g_switchRaw && (now - g_switchChangedMs) >= kDebounceMs) {
            // Raw sample stable for kDebounceMs -> accept new state.
            g_switchRaw = raw;
            if (raw) {
                g_switchPressedMs = now;
                g_longPressFired = false;
                if (event == Event::None) {
                    event = Event::Press;
                }
            } else {
                if (event == Event::None) {
                    event = Event::Release;
                }
            }
        }

        // Long press fires once while the switch stays held.
        if (g_switchRaw && !g_longPressFired &&
            (now - g_switchPressedMs) >= kLongPressMs) {
            g_longPressFired = true;
            if (event == Event::None) {
                event = Event::LongPress;
            }
        }

        return event;
    }

} // namespace rotaryinput
