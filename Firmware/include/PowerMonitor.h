/**
 * @file PowerMonitor.h
 * @brief INA219 based power monitoring for the LED strip supply
 *
 * @copyright Marc Ketel
 * SPDX-License-Identifier: Apache-2.0
 */

#pragma once

namespace powermonitor {
    // Initialise the INA219 at 0x40. Returns false when the sensor is not found.
    bool begin();

    // True when the sensor responded during begin().
    bool present();

    // Latest measurement (cached by sample()).
    float busVoltage();
    float currentMilliAmps();
    float powerMilliWatts();

    // Take a fresh sample from the sensor. Returns false when unavailable.
    bool sample();
}
