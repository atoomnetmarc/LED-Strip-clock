/**
 * @file RotaryService.cpp
 * @brief MCP23008-backed rotary encoder service implementation.
 *
 * @copyright Marc Ketel
 * SPDX-License-Identifier: Apache-2.0
 */

#include <Arduino.h>
#include <MCP23008.h>

#include "Log.h"
#include "Pins.h"
#include "RotaryService.h"

namespace rotary {

    namespace {

        const char TAG[] = "rotary";

        constexpr uint8_t kExpanderAddress = 0x20; // A0/A1/A2 tied to GND
        constexpr uint8_t kEncoderPinMask = 0x07;  // bits 0-2: A, B, switch
        // Always poll fast: a slow poll interval misses the short quadrature
        // transitions of a detent, so the first turns after idle would be
        // discarded until a sample happens to land on a valid edge.
        constexpr uint32_t kPollIntervalMs = 2;

        MCP23008 expander(kExpanderAddress);
        EventHandler handler = nullptr;

        uint32_t pollTimer = 0;

        void dispatch(Event event) {
            if (handler) {
                handler(event);
            }
        }

    } // namespace

    bool begin(EventHandler eventHandler) {
        handler = eventHandler;

        if (!expander.begin()) {
            LOGE(TAG, "MCP23008 not found at 0x%02X", kExpanderAddress);
            return false;
        }

        expander.pinMode8(kEncoderPinMask); // bits 0-2 input
        expander.setPullup8(kEncoderPinMask);
        rotaryinput::begin(PIN_IO_ROT_A, PIN_IO_ROT_B, PIN_IO_ROT_SW);

        LOGI(TAG, "MCP23008 ready");
        return true;
    }

    void loop() {
        uint32_t now = millis();

        if (now - pollTimer < kPollIntervalMs) {
            return;
        }
        pollTimer = now;

        uint8_t port = expander.read8();
        if (port == MCP23008_INVALID_READ) {
            return; // I2C error, skip this sample
        }

        Event event = rotaryinput::update(port);
        if (event != Event::None) {
            dispatch(event);
        }
    }

} // namespace rotary
