/**
 * @file RotaryService.h
 * @brief Rotary encoder service (MCP23008-backed).
 *
 * Owns the MCP23008 I/O expander, polls the port register at an adaptive
 * rate and decodes the rotary encoder via rotaryinput. Events are delivered
 * to a user-supplied callback.
 *
 * @copyright Marc Ketel
 * SPDX-License-Identifier: Apache-2.0
 */

#pragma once

#include <stdint.h>

#include "RotaryInput.h"

namespace rotary {

    using Event = rotaryinput::Event;

    /// Callback invoked for every decoded encoder/switch event.
    using EventHandler = void (*)(Event event);

    /**
     * @brief Initialize the MCP23008 and the decoder.
     *
     * @param handler Callback for encoder events (may be nullptr).
     * @return true when the MCP23008 responded.
     */
    bool begin(EventHandler handler);

    /**
     * @brief Poll the expander; call from loop().
     *
     * Polls fast (2 ms) for 2 s after the last event, then slows down to 50 ms
     * to keep the I2C bus free.
     */
    void loop();

} // namespace rotary
