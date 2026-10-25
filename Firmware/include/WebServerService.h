/**
 * @file WebServerService.h
 * @brief Embedded web UI, API and OTA server
 *
 * @copyright Marc Ketel
 * SPDX-License-Identifier: Apache-2.0
 */

#pragma once

#include <Arduino.h>

namespace webserver {
    // Start the HTTP server (read-only on STA). Call after configstore::begin().
    void setup();

    // Record a successful NTP sync (called from the settimeofday callback).
    void noteNtpSync();

    // Call from loop(): serves HTTP, runs captive DNS in portal mode and
    // opens the AP config portal as fallback when STA stays disconnected.
    void loop();

    // True while the AP config portal is open (writes allowed without login).
    bool portalActive();

    // Manually start/stop the AP config portal.
    void beginPortal();
    void endPortal();

    // Re-apply network and time settings from the stored config without a
    // reboot (hostname, timezone/NTP, WiFi reconnect when pending).
    void applyLiveConfig();
}
