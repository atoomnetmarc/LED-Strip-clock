/**
 * @file RotaryInput.h
 * @brief Rotary encoder (A/B/switch) behind an MCP23008 I/O expander.
 *
 * Polls the MCP23008 port register and decodes the quadrature signal with a
 * full 4-state state machine. One mechanical detent equals 4 quadrature edges,
 * so the decoder accumulates edges and emits exactly one step per detent,
 * which makes it robust against missed edges at polling rates as low as 1 ms.
 *
 * The switch is debounced in software (stable for DEBOUNCE_MS) and supports
 * short and long press events.
 *
 * @copyright Marc Ketel
 * SPDX-License-Identifier: Apache-2.0
 */

#pragma once

#include <stdint.h>

namespace rotaryinput {

    enum class Event : uint8_t {
        None,
        Cw,       ///< one detent clockwise
        Ccw,      ///< one detent counter-clockwise
        Press,    ///< switch pressed (after debounce)
        Release,  ///< switch released
        LongPress ///< switch held for LONG_PRESS_MS
    };

    /**
     * @brief Initialize the decoder.
     *
     * @param portMaskBitsA Bit position of encoder A in the MCP23008 port register (0..7).
     * @param portMaskBitsB Bit position of encoder B in the MCP23008 port register (0..7).
     * @param portMaskBitsSw Bit position of the switch in the MCP23008 port register (0..7).
     * @param activeLowSwitch True when the switch pulls the pin to GND (typical, with pull-up).
     */
    void begin(uint8_t portMaskBitsA, uint8_t portMaskBitsB, uint8_t portMaskBitsSw,
               bool activeLowSwitch = true);

    /**
     * @brief Feed one snapshot of the MCP23008 port register into the decoder.
     *
     * Call this at a fixed interval (1-2 ms recommended while the encoder is in
     * use; slower is fine when idle). Reads the port once via MCP23008::read8()
     * and passes the value here, so the I2C transaction stays outside this class.
     *
     * @return The event produced by this sample, or Event::None.
     */
    Event update(uint8_t portValue);

} // namespace rotaryinput
