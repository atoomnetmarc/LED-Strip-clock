/**
 * @file PowerMonitor.cpp
 * @brief INA219 based power monitoring for the LED strip supply
 *
 * @copyright Marc Ketel
 * SPDX-License-Identifier: Apache-2.0
 */

#include "PowerMonitor.h"

#include <INA219.h>
#include <Wire.h>

#include "Log.h"

namespace powermonitor {
    namespace {
        const char TAG[] = "power";
        constexpr uint8_t INA_ADDRESS = 0x40;

        INA219 ina(INA_ADDRESS);
        bool available = false;

        float busV = 0.0f;
        float currentMa = 0.0f;
        float powerMw = 0.0f;
    } // namespace

    bool begin() {
        // 400 kHz I2C, matching the shared bus.
        ina.begin();
        // Max 3.2 A / 3200 mA with the default calibration of the library.
        if (!ina.setMaxCurrentShunt(3.2, 0.1)) {
            LOGE(TAG, "INA219 not found at 0x%02X", INA_ADDRESS);
            available = false;
            return false;
        }
        available = true;
        LOGI(TAG, "INA219 ready at 0x%02X", INA_ADDRESS);
        return true;
    }

    bool present() {
        return available;
    }

    float busVoltage() {
        return busV;
    }

    float currentMilliAmps() {
        return currentMa;
    }

    float powerMilliWatts() {
        return powerMw;
    }

    bool sample() {
        if (!available) {
            return false;
        }

        busV = ina.getBusVoltage();
        currentMa = ina.getCurrent_mA();
        powerMw = ina.getPower_mW();
        return true;
    }
}
